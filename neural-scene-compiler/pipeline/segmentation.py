"""
Segmentation Module - Neural Scene Compiler Pipeline Stage 1

Purpose:
    Uses the Segment Anything Model (SAM) to detect and segment all objects
    in an input image. Each unique region/object gets its own binary mask,
    which is passed to downstream stages (classification, depth, scene graph).

Usage:
    python segmentation.py <input_image_path> [--output-dir <dir>]

Expected Output:
    - output/<name>_segmented.png  : image with colored overlays on masks
    - output/masks/mask_0.png, mask_1.png, ...  : individual binary masks
    - returns list of mask dicts for use by classification.py
"""

import argparse
import os
import sys

import cv2
import numpy as np

# SAM imports — install with: pip install segment-anything
try:
    from segment_anything import SamAutomaticMaskGenerator, sam_model_registry
    SAM_AVAILABLE = True
except ImportError:
    SAM_AVAILABLE = False


# --------------------------------------------------------------------------- #
#  Constants                                                                   #
# --------------------------------------------------------------------------- #

# Default SAM checkpoint; download from:
# https://dl.fbaipublicfiles.com/segment_anything/sam_vit_h_4b8939.pth
DEFAULT_CHECKPOINT = os.path.join(
    os.path.dirname(__file__), "..", "models", "sam_vit_h_4b8939.pth"
)
DEFAULT_MODEL_TYPE = "vit_h"

# Minimum mask area (pixels) — filters out tiny noise regions
MIN_MASK_AREA = 500


# --------------------------------------------------------------------------- #
#  Core functions                                                              #
# --------------------------------------------------------------------------- #

def load_sam_model(checkpoint: str = DEFAULT_CHECKPOINT,
                   model_type: str = DEFAULT_MODEL_TYPE,
                   device: str = "cuda"):
    """
    Load SAM from a local checkpoint file.

    Args:
        checkpoint:  Path to the .pth weights file.
        model_type:  One of 'vit_h', 'vit_l', 'vit_b'.
        device:      'cuda' for GPU or 'cpu' as fallback.

    Returns:
        SamAutomaticMaskGenerator ready to produce masks.
    """
    if not SAM_AVAILABLE:
        raise ImportError(
            "segment-anything is not installed. "
            "Run: pip install segment-anything"
        )
    if not os.path.exists(checkpoint):
        raise FileNotFoundError(
            f"SAM checkpoint not found at: {checkpoint}\n"
            "Download it from:\n"
            "  https://dl.fbaipublicfiles.com/segment_anything/sam_vit_h_4b8939.pth\n"
            f"and place it at {checkpoint}"
        )

    print(f"[Segmentation] Loading SAM model ({model_type}) from {checkpoint}")
    sam = sam_model_registry[model_type](checkpoint=checkpoint)
    sam.to(device=device)

    # Automatic mask generator with default hyper-parameters
    mask_generator = SamAutomaticMaskGenerator(
        model=sam,
        points_per_side=32,         # grid density for automatic prompting
        pred_iou_thresh=0.88,       # keep high-confidence masks
        stability_score_thresh=0.95,
        min_mask_region_area=MIN_MASK_AREA,
    )
    print("[Segmentation] SAM model loaded successfully.")
    return mask_generator


def run_segmentation(image_bgr: np.ndarray,
                     mask_generator) -> list:
    """
    Run SAM on an image and return a sorted list of mask dictionaries.

    Each dict contains (at minimum):
        'segmentation' : bool 2-D array (H x W)
        'area'         : int, number of True pixels
        'bbox'         : [x, y, w, h] in pixel coordinates

    Args:
        image_bgr:       Image loaded with cv2 (BGR channel order).
        mask_generator:  SamAutomaticMaskGenerator instance.

    Returns:
        List of mask dicts, sorted largest-to-smallest by area.
    """
    # SAM expects RGB
    image_rgb = cv2.cvtColor(image_bgr, cv2.COLOR_BGR2RGB)

    print("[Segmentation] Generating masks — this may take a few seconds …")
    masks = mask_generator.generate(image_rgb)

    # Sort by area descending (largest objects first)
    masks = sorted(masks, key=lambda m: m["area"], reverse=True)
    print(f"[Segmentation] {len(masks)} masks generated.")
    return masks


def save_masks(image_bgr: np.ndarray,
               masks: list,
               output_dir: str) -> list:
    """
    Save individual binary masks and a composite overlay image.

    Args:
        image_bgr:   Original image (BGR).
        masks:       List of mask dicts from run_segmentation().
        output_dir:  Root output directory.

    Returns:
        List of file paths for saved per-mask PNG files.
    """
    masks_dir = os.path.join(output_dir, "masks")
    os.makedirs(masks_dir, exist_ok=True)

    saved_paths = []
    overlay = image_bgr.copy()

    rng = np.random.default_rng(seed=42)

    for idx, mask_data in enumerate(masks):
        binary = mask_data["segmentation"].astype(np.uint8) * 255

        # Save individual binary mask
        mask_path = os.path.join(masks_dir, f"mask_{idx}.png")
        cv2.imwrite(mask_path, binary)
        saved_paths.append(mask_path)

        # Draw colored overlay on composite image
        color = rng.integers(64, 255, size=3).tolist()
        overlay[mask_data["segmentation"]] = (
            overlay[mask_data["segmentation"]] * 0.5
            + np.array(color) * 0.5
        ).astype(np.uint8)

    # Save composite overlay
    overlay_path = os.path.join(output_dir, "segmented_overlay.png")
    cv2.imwrite(overlay_path, overlay)
    print(f"[Segmentation] Overlay saved to {overlay_path}")
    print(f"[Segmentation] Individual masks saved to {masks_dir}/")
    return saved_paths


def crop_object_regions(image_bgr: np.ndarray, masks: list) -> list:
    """
    Crop each masked region from the image for use by the classifier.

    Args:
        image_bgr:  Original image.
        masks:      List of mask dicts.

    Returns:
        List of BGR crops, one per mask.
    """
    crops = []
    for mask_data in masks:
        x, y, w, h = mask_data["bbox"]
        x, y, w, h = int(x), int(y), int(w), int(h)
        crop = image_bgr[y: y + h, x: x + w]
        crops.append(crop)
    return crops


# --------------------------------------------------------------------------- #
#  CLI entry-point                                                             #
# --------------------------------------------------------------------------- #

def parse_args():
    parser = argparse.ArgumentParser(
        description="SAM-based segmentation — Neural Scene Compiler Stage 1"
    )
    parser.add_argument("image", help="Path to input image")
    parser.add_argument(
        "--output-dir", default=os.path.join(os.path.dirname(__file__),
                                             "..", "output"),
        help="Directory to save outputs (default: ../output)"
    )
    parser.add_argument(
        "--checkpoint", default=DEFAULT_CHECKPOINT,
        help="Path to SAM checkpoint .pth file"
    )
    parser.add_argument(
        "--model-type", default=DEFAULT_MODEL_TYPE,
        choices=["vit_h", "vit_l", "vit_b"],
        help="SAM model variant (default: vit_h)"
    )
    parser.add_argument(
        "--device", default="cuda",
        choices=["cuda", "cpu"],
        help="Compute device (default: cuda)"
    )
    return parser.parse_args()


def main():
    args = parse_args()

    if not os.path.exists(args.image):
        print(f"[Error] Image not found: {args.image}", file=sys.stderr)
        sys.exit(1)

    # Load image
    image = cv2.imread(args.image)
    if image is None:
        print(f"[Error] Cannot read image: {args.image}", file=sys.stderr)
        sys.exit(1)
    print(f"[Segmentation] Loaded image {args.image}  shape={image.shape}")

    os.makedirs(args.output_dir, exist_ok=True)

    # Load model and run segmentation
    mask_generator = load_sam_model(
        checkpoint=args.checkpoint,
        model_type=args.model_type,
        device=args.device,
    )
    masks = run_segmentation(image, mask_generator)

    # Save results
    save_masks(image, masks, args.output_dir)

    print("\n[Segmentation] Done.")
    print(f"  Objects found : {len(masks)}")
    print(f"  Next step     : run classification.py to identify each object")


if __name__ == "__main__":
    main()
