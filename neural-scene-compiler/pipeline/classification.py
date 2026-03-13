"""
Classification Module - Neural Scene Compiler Pipeline Stage 2

Purpose:
    Takes the object crops produced by the segmentation module and uses
    OpenAI CLIP to assign a natural-language label to each crop.
    CLIP compares each crop against a candidate vocabulary and returns
    the most likely object name — no fine-tuning required.

Usage:
    python classification.py <input_image_path> [--output-dir <dir>]

    When called standalone the module re-runs segmentation internally.
    In the full pipeline it receives masks from segmentation.py directly.

Expected Output:
    - Prints detected objects to stdout:
        object_1 : laptop
        object_2 : mug
        object_3 : notebook
    - Returns a list of (label, confidence) pairs for each mask.
"""

import argparse
import os
import sys

import cv2
import numpy as np

# CLIP imports — install with: pip install open-clip-torch
# (or the original: pip install git+https://github.com/openai/CLIP)
try:
    import open_clip
    import torch
    from PIL import Image as PILImage

    CLIP_AVAILABLE = True
except ImportError:
    CLIP_AVAILABLE = False


# --------------------------------------------------------------------------- #
#  Candidate object vocabulary                                                 #
#  Extend this list to recognise more objects in the scene.                   #
# --------------------------------------------------------------------------- #

CANDIDATE_LABELS = [
    "laptop", "monitor", "keyboard", "mouse",
    "mug", "cup", "bottle", "glass",
    "book", "notebook", "pen", "pencil",
    "chair", "table", "desk", "shelf",
    "phone", "tablet", "headphones", "lamp",
    "plant", "vase", "clock", "picture frame",
    "backpack", "bag", "box", "drawer",
    "person", "cat", "dog",
    "wall", "floor", "ceiling", "window", "door",
]

# Prompt template improves zero-shot accuracy
PROMPT_TEMPLATE = "a photo of a {}"


# --------------------------------------------------------------------------- #
#  Core functions                                                              #
# --------------------------------------------------------------------------- #

def load_clip_model(model_name: str = "ViT-B-32",
                    pretrained: str = "openai",
                    device: str = "cuda"):
    """
    Load an OpenCLIP model and its preprocessing transform.

    Args:
        model_name:  CLIP architecture, e.g. 'ViT-B-32', 'ViT-L-14'.
        pretrained:  Weights tag, e.g. 'openai', 'laion2b_s34b_b79k'.
        device:      'cuda' or 'cpu'.

    Returns:
        (model, preprocess_fn, tokenizer)
    """
    if not CLIP_AVAILABLE:
        raise ImportError(
            "open_clip_torch is not installed. "
            "Run: pip install open-clip-torch"
        )

    print(f"[Classification] Loading CLIP model ({model_name}, {pretrained}) …")
    model, _, preprocess = open_clip.create_model_and_transforms(
        model_name, pretrained=pretrained
    )
    model.eval()
    model.to(device)
    tokenizer = open_clip.get_tokenizer(model_name)
    print("[Classification] CLIP model loaded.")
    return model, preprocess, tokenizer


def encode_text_labels(labels: list,
                       model,
                       tokenizer,
                       device: str = "cuda") -> "torch.Tensor":
    """
    Pre-compute normalised text embeddings for the candidate label list.

    Args:
        labels:    List of string labels.
        model:     CLIP model.
        tokenizer: CLIP tokenizer.
        device:    Compute device.

    Returns:
        Tensor of shape (num_labels, embedding_dim), L2-normalised.
    """
    import torch

    prompts = [PROMPT_TEMPLATE.format(lbl) for lbl in labels]
    tokens = tokenizer(prompts).to(device)

    with torch.no_grad():
        text_features = model.encode_text(tokens)
        text_features = text_features / text_features.norm(dim=-1, keepdim=True)

    return text_features


def classify_crops(crops: list,
                   model,
                   preprocess,
                   text_features: "torch.Tensor",
                   labels: list,
                   device: str = "cuda") -> list:
    """
    Classify each image crop using cosine similarity against text embeddings.

    Args:
        crops:         List of BGR numpy arrays (one per segmented object).
        model:         CLIP model.
        preprocess:    CLIP image pre-processing transform.
        text_features: Pre-computed text embeddings (num_labels, dim).
        labels:        Candidate label strings (same order as text_features).
        device:        Compute device.

    Returns:
        List of dicts: [{'label': str, 'confidence': float}, …]
    """
    import torch

    results = []
    for idx, crop in enumerate(crops):
        if crop is None or crop.size == 0:
            results.append({"label": "unknown", "confidence": 0.0})
            continue

        # Convert BGR crop to PIL RGB image
        crop_rgb = cv2.cvtColor(crop, cv2.COLOR_BGR2RGB)
        pil_img = PILImage.fromarray(crop_rgb)

        image_input = preprocess(pil_img).unsqueeze(0).to(device)

        with torch.no_grad():
            image_features = model.encode_image(image_input)
            image_features = image_features / image_features.norm(
                dim=-1, keepdim=True
            )

        # Cosine similarity → probabilities via softmax
        logits = (100.0 * image_features @ text_features.T).softmax(dim=-1)
        best_idx = logits[0].argmax().item()
        confidence = logits[0][best_idx].item()

        results.append({
            "label": labels[best_idx],
            "confidence": round(confidence, 4),
        })

    return results


def print_classification_results(results: list) -> None:
    """Print results in the expected output format."""
    print("\n[Classification] Detected objects:")
    for i, res in enumerate(results, start=1):
        print(f"  object_{i:02d} : {res['label']}  (confidence={res['confidence']:.2%})")


# --------------------------------------------------------------------------- #
#  CLI entry-point (standalone mode)                                           #
# --------------------------------------------------------------------------- #

def parse_args():
    parser = argparse.ArgumentParser(
        description="CLIP-based classification — Neural Scene Compiler Stage 2"
    )
    parser.add_argument("image", help="Path to input image")
    parser.add_argument(
        "--output-dir",
        default=os.path.join(os.path.dirname(__file__), "..", "output"),
        help="Directory that contains masks/ from segmentation stage",
    )
    parser.add_argument(
        "--checkpoint",
        default=os.path.join(
            os.path.dirname(__file__), "..", "models", "sam_vit_h_4b8939.pth"
        ),
        help="SAM checkpoint (used when running standalone)",
    )
    parser.add_argument("--device", default="cuda", choices=["cuda", "cpu"])
    return parser.parse_args()


def main():
    args = parse_args()

    if not os.path.exists(args.image):
        print(f"[Error] Image not found: {args.image}", file=sys.stderr)
        sys.exit(1)

    image = cv2.imread(args.image)
    if image is None:
        print(f"[Error] Cannot read image: {args.image}", file=sys.stderr)
        sys.exit(1)

    # Run segmentation to get crops
    from segmentation import (
        crop_object_regions,
        load_sam_model,
        run_segmentation,
    )

    mask_gen = load_sam_model(checkpoint=args.checkpoint, device=args.device)
    masks = run_segmentation(image, mask_gen)
    crops = crop_object_regions(image, masks)

    # Run classification
    model, preprocess, tokenizer = load_clip_model(device=args.device)
    text_features = encode_text_labels(
        CANDIDATE_LABELS, model, tokenizer, device=args.device
    )
    results = classify_crops(
        crops, model, preprocess, text_features, CANDIDATE_LABELS,
        device=args.device
    )
    print_classification_results(results)

    print("\n[Classification] Done.")
    print("  Next step: run depth.py to estimate per-object depth.")


if __name__ == "__main__":
    main()
