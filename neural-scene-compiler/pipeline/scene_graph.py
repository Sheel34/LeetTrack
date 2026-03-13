"""
Scene Graph Module - Neural Scene Compiler Pipeline Stage 4

Purpose:
    Combines the outputs of segmentation, classification, and depth estimation
    to build a structured scene graph — a JSON representation that describes
    the objects in the scene, their labels, 3-D positions, and spatial
    relationships to one another.

    The (x, y) coordinates come from the bounding-box centroids in pixel
    space, normalised to [-1, 1].  The z coordinate comes from MiDaS depth.

Output format example:
    {
      "objects": [
        {"id": 0, "name": "laptop",   "position": [x, y, z], "bbox": [...]},
        {"id": 1, "name": "mug",      "position": [x, y, z], "bbox": [...]}
      ],
      "relations": [
        {"subject": "mug", "relation": "left_of", "object": "laptop"}
      ]
    }

Usage:
    python scene_graph.py <input_image_path> [--output-dir <dir>]
"""

import argparse
import json
import os
import sys

import cv2
import numpy as np


# --------------------------------------------------------------------------- #
#  Spatial relation helpers                                                    #
# --------------------------------------------------------------------------- #

def _infer_relations(objects: list) -> list:
    """
    Derive simple pairwise spatial relations from normalised (x, y, z).

    Supported relations: left_of, right_of, above, below, in_front_of,
    behind.  Only the most significant axis determines the relation.

    Args:
        objects:  List of scene-object dicts (each has 'name', 'position').

    Returns:
        List of relation dicts.
    """
    relations = []
    for i, a in enumerate(objects):
        for j, b in enumerate(objects):
            if i >= j:
                continue

            ax, ay, az = a["position"]
            bx, by, bz = b["position"]
            dx, dy, dz = bx - ax, by - ay, bz - az

            # Only emit a relation when the difference is non-trivial
            threshold = 0.15
            if abs(dx) > threshold or abs(dy) > threshold or abs(dz) > threshold:
                # Pick the dominant axis
                dominant = max(
                    [("x", abs(dx)), ("y", abs(dy)), ("z", abs(dz))],
                    key=lambda t: t[1],
                )[0]

                if dominant == "x":
                    rel = "left_of" if dx > 0 else "right_of"
                elif dominant == "y":
                    rel = "below" if dy > 0 else "above"
                else:
                    rel = "behind" if dz > 0 else "in_front_of"

                relations.append({
                    "subject": a["name"],
                    "relation": rel,
                    "object": b["name"],
                })

    return relations


# --------------------------------------------------------------------------- #
#  Core functions                                                              #
# --------------------------------------------------------------------------- #

def build_scene_graph(masks: list,
                      labels: list,
                      depth_map: np.ndarray,
                      image_shape: tuple) -> dict:
    """
    Construct the scene graph from pipeline outputs.

    Args:
        masks:        List of SAM mask dicts (each has 'segmentation', 'bbox').
        labels:       List of classification result dicts {'label', 'confidence'}.
        depth_map:    Normalised depth array (H x W) from MiDaS.
        image_shape:  (H, W) of the original image.

    Returns:
        Scene graph dict with 'objects' and 'relations' keys.
    """
    H, W = image_shape

    scene_objects = []
    for idx, (mask_data, label_data) in enumerate(zip(masks, labels)):
        x, y, w, h = mask_data["bbox"]
        x, y, w, h = int(x), int(y), int(w), int(h)

        # Centroid in pixel space
        cx_px = x + w / 2.0
        cy_px = y + h / 2.0

        # Normalise (x, y) to [-1, 1]  (origin = image centre)
        cx_norm = round((cx_px / W) * 2.0 - 1.0, 4)
        cy_norm = round((cy_px / H) * 2.0 - 1.0, 4)

        # Depth: median over the object mask
        mask_bool = mask_data["segmentation"]
        z_raw = float(np.median(depth_map[mask_bool])) if mask_bool.any() else 0.5
        # Remap z to [-1, 1]  (1 = closest, -1 = farthest)
        z_norm = round(z_raw * 2.0 - 1.0, 4)

        scene_objects.append({
            "id": idx,
            "name": label_data["label"],
            "confidence": label_data["confidence"],
            "position": [cx_norm, cy_norm, z_norm],   # [x, y, z]
            "bbox_pixels": [x, y, w, h],
            "area_pixels": int(mask_data["area"]),
        })

    relations = _infer_relations(scene_objects)

    scene_graph = {
        "objects": scene_objects,
        "relations": relations,
    }
    return scene_graph


def save_scene_graph(scene_graph: dict, output_dir: str) -> str:
    """
    Write the scene graph to a JSON file.

    Args:
        scene_graph:  Dict returned by build_scene_graph().
        output_dir:   Root output directory.

    Returns:
        Path to saved JSON file.
    """
    os.makedirs(output_dir, exist_ok=True)
    out_path = os.path.join(output_dir, "scene_graph.json")

    with open(out_path, "w", encoding="utf-8") as fh:
        json.dump(scene_graph, fh, indent=2)

    print(f"[SceneGraph] Scene graph saved to {out_path}")
    return out_path


def print_scene_graph(scene_graph: dict) -> None:
    """Pretty-print the scene graph to stdout."""
    print("\n[SceneGraph] Scene representation:")
    print(json.dumps(scene_graph, indent=2))


# --------------------------------------------------------------------------- #
#  CLI entry-point (standalone mode — runs full pipeline up to this stage)    #
# --------------------------------------------------------------------------- #

def parse_args():
    parser = argparse.ArgumentParser(
        description="Scene graph builder — Neural Scene Compiler Stage 4"
    )
    parser.add_argument("image", help="Path to input image")
    parser.add_argument(
        "--output-dir",
        default=os.path.join(os.path.dirname(__file__), "..", "output"),
    )
    parser.add_argument(
        "--sam-checkpoint",
        default=os.path.join(
            os.path.dirname(__file__), "..", "models", "sam_vit_h_4b8939.pth"
        ),
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

    # --- Stage 1: Segmentation ---
    from segmentation import (
        crop_object_regions,
        load_sam_model,
        run_segmentation,
        save_masks,
    )

    mask_gen = load_sam_model(
        checkpoint=args.sam_checkpoint, device=args.device
    )
    masks = run_segmentation(image, mask_gen)
    save_masks(image, masks, args.output_dir)
    crops = crop_object_regions(image, masks)

    # --- Stage 2: Classification ---
    from classification import (
        CANDIDATE_LABELS,
        classify_crops,
        encode_text_labels,
        load_clip_model,
        print_classification_results,
    )

    clip_model, preprocess, tokenizer = load_clip_model(device=args.device)
    text_features = encode_text_labels(
        CANDIDATE_LABELS, clip_model, tokenizer, device=args.device
    )
    labels = classify_crops(
        crops, clip_model, preprocess, text_features, CANDIDATE_LABELS,
        device=args.device,
    )
    print_classification_results(labels)

    # --- Stage 3: Depth ---
    from depth import estimate_depth, load_midas_model, save_depth_outputs

    midas_model, transform = load_midas_model(device=args.device)
    depth_map = estimate_depth(image, midas_model, transform, device=args.device)
    save_depth_outputs(depth_map, args.output_dir)

    # --- Stage 4: Scene graph ---
    H, W = image.shape[:2]
    scene_graph = build_scene_graph(masks, labels, depth_map, (H, W))
    save_scene_graph(scene_graph, args.output_dir)
    print_scene_graph(scene_graph)

    print("\n[SceneGraph] Done.")
    print("  Next step: run blender_generator.py to create the 3-D scene.")


if __name__ == "__main__":
    main()
