"""
run_demo.py — End-to-end Neural Scene Compiler demo

Purpose:
    Runs the full pipeline on a single input image:
        1. Segmentation   (SAM)
        2. Classification (CLIP)
        3. Depth          (MiDaS)
        4. Scene Graph    (JSON)
        5. Blender Script (optional execution)

Usage:
    python run_demo.py --image <path/to/image.jpg>

    # With a custom SAM checkpoint location:
    python run_demo.py --image demo_input.jpg --sam-checkpoint ../models/sam_vit_h_4b8939.pth

    # To also execute Blender (must be installed):
    python run_demo.py --image demo_input.jpg --run-blender

All outputs are written to ../output/ by default.
"""

import argparse
import os
import sys
import time

# Ensure the pipeline directory is importable regardless of cwd
PIPELINE_DIR = os.path.join(os.path.dirname(__file__), "..", "pipeline")
sys.path.insert(0, os.path.abspath(PIPELINE_DIR))

OUTPUT_DIR = os.path.abspath(
    os.path.join(os.path.dirname(__file__), "..", "output")
)


# --------------------------------------------------------------------------- #
#  Argument parsing                                                            #
# --------------------------------------------------------------------------- #

def parse_args():
    parser = argparse.ArgumentParser(
        description="Neural Scene Compiler — full pipeline demo"
    )
    parser.add_argument(
        "--image",
        required=True,
        help="Path to input image (JPG / PNG)",
    )
    parser.add_argument(
        "--output-dir",
        default=OUTPUT_DIR,
        help="Directory to write all outputs (default: ../output)",
    )
    parser.add_argument(
        "--sam-checkpoint",
        default=os.path.join(
            os.path.dirname(__file__), "..", "models", "sam_vit_h_4b8939.pth"
        ),
        help="Path to SAM model weights (.pth)",
    )
    parser.add_argument(
        "--sam-model-type",
        default="vit_h",
        choices=["vit_h", "vit_l", "vit_b"],
        help="SAM variant (default: vit_h)",
    )
    parser.add_argument(
        "--midas-model-type",
        default="DPT_Large",
        choices=["DPT_Large", "DPT_Hybrid", "MiDaS_small"],
        help="MiDaS variant (default: DPT_Large)",
    )
    parser.add_argument(
        "--device",
        default="cuda",
        choices=["cuda", "cpu"],
        help="Compute device (default: cuda, falls back to cpu automatically)",
    )
    parser.add_argument(
        "--run-blender",
        action="store_true",
        help="Execute Blender after generating the scene script",
    )
    parser.add_argument(
        "--blender-executable",
        default="blender",
        help="Path to Blender binary",
    )
    return parser.parse_args()


# --------------------------------------------------------------------------- #
#  Pipeline runner                                                             #
# --------------------------------------------------------------------------- #

def run_pipeline(args):
    import cv2

    # --------------------------------------------------------------------- #
    #  Validate input                                                         #
    # --------------------------------------------------------------------- #
    if not os.path.exists(args.image):
        print(f"[Demo] ERROR: Input image not found: {args.image}")
        sys.exit(1)

    image = cv2.imread(args.image)
    if image is None:
        print(f"[Demo] ERROR: Cannot read image: {args.image}")
        sys.exit(1)

    os.makedirs(args.output_dir, exist_ok=True)
    print(f"\n{'='*60}")
    print("  Neural Scene Compiler — Demo Pipeline")
    print(f"{'='*60}")
    print(f"  Input  : {args.image}  ({image.shape[1]}x{image.shape[0]}px)")
    print(f"  Output : {args.output_dir}")
    print(f"  Device : {args.device}")
    print(f"{'='*60}\n")

    # Resolve device: fall back to CPU if CUDA is not available
    device = args.device
    try:
        import torch
        if device == "cuda" and not torch.cuda.is_available():
            print("[Demo] CUDA not available — falling back to CPU.")
            device = "cpu"
    except ImportError:
        device = "cpu"

    total_start = time.perf_counter()

    # --------------------------------------------------------------------- #
    #  Stage 1 — Segmentation                                                #
    # --------------------------------------------------------------------- #
    print("\n[Stage 1/5] Segmentation")
    print("-" * 40)
    t0 = time.perf_counter()

    from segmentation import (
        crop_object_regions,
        load_sam_model,
        run_segmentation,
        save_masks,
    )

    mask_gen = load_sam_model(
        checkpoint=args.sam_checkpoint,
        model_type=args.sam_model_type,
        device=device,
    )
    masks = run_segmentation(image, mask_gen)
    save_masks(image, masks, args.output_dir)
    crops = crop_object_regions(image, masks)
    print(f"[Stage 1] Done in {time.perf_counter() - t0:.1f}s  "
          f"({len(masks)} segments found)")

    # --------------------------------------------------------------------- #
    #  Stage 2 — Classification                                              #
    # --------------------------------------------------------------------- #
    print("\n[Stage 2/5] Classification")
    print("-" * 40)
    t0 = time.perf_counter()

    from classification import (
        CANDIDATE_LABELS,
        classify_crops,
        encode_text_labels,
        load_clip_model,
        print_classification_results,
    )

    clip_model, preprocess, tokenizer = load_clip_model(device=device)
    text_features = encode_text_labels(
        CANDIDATE_LABELS, clip_model, tokenizer, device=device
    )
    labels = classify_crops(
        crops, clip_model, preprocess, text_features, CANDIDATE_LABELS,
        device=device,
    )
    print_classification_results(labels)
    print(f"[Stage 2] Done in {time.perf_counter() - t0:.1f}s")

    # --------------------------------------------------------------------- #
    #  Stage 3 — Depth Estimation                                            #
    # --------------------------------------------------------------------- #
    print("\n[Stage 3/5] Depth Estimation")
    print("-" * 40)
    t0 = time.perf_counter()

    from depth import estimate_depth, load_midas_model, save_depth_outputs

    midas_model, transform = load_midas_model(
        model_type=args.midas_model_type, device=device
    )
    depth_map = estimate_depth(image, midas_model, transform, device=device)
    save_depth_outputs(depth_map, args.output_dir)
    print(f"[Stage 3] Done in {time.perf_counter() - t0:.1f}s")

    # --------------------------------------------------------------------- #
    #  Stage 4 — Scene Graph                                                 #
    # --------------------------------------------------------------------- #
    print("\n[Stage 4/5] Scene Graph Generation")
    print("-" * 40)
    t0 = time.perf_counter()

    from scene_graph import (
        build_scene_graph,
        print_scene_graph,
        save_scene_graph,
    )

    H, W = image.shape[:2]
    scene_graph = build_scene_graph(masks, labels, depth_map, (H, W))
    save_scene_graph(scene_graph, args.output_dir)
    print_scene_graph(scene_graph)
    print(f"[Stage 4] Done in {time.perf_counter() - t0:.1f}s")

    # --------------------------------------------------------------------- #
    #  Stage 5 — Blender Scene Generation                                    #
    # --------------------------------------------------------------------- #
    print("\n[Stage 5/5] Blender Scene Generation")
    print("-" * 40)
    t0 = time.perf_counter()

    from blender_generator import (
        build_blender_script,
        run_blender,
        save_blender_script,
    )

    blend_path = os.path.abspath(os.path.join(args.output_dir, "scene.blend"))
    script = build_blender_script(scene_graph, blend_path)
    script_path = save_blender_script(script, args.output_dir)

    if args.run_blender:
        rc = run_blender(script_path, args.blender_executable)
        blend_status = "saved" if rc == 0 else "ERROR (see above)"
    else:
        blend_status = "script only (use --run-blender to execute)"
    print(f"[Stage 5] Done in {time.perf_counter() - t0:.1f}s")

    # --------------------------------------------------------------------- #
    #  Summary                                                               #
    # --------------------------------------------------------------------- #
    total_time = time.perf_counter() - total_start
    print(f"\n{'='*60}")
    print("  Pipeline Complete")
    print(f"{'='*60}")
    print(f"  Total time        : {total_time:.1f}s")
    print(f"  Objects detected  : {len(labels)}")
    print(f"\n  Outputs written to {args.output_dir}/")
    print(f"    segmented_overlay.png")
    print(f"    masks/mask_N.png")
    print(f"    depth_map.png")
    print(f"    depth_raw.npy")
    print(f"    scene_graph.json")
    print(f"    blender_scene.py")
    print(f"    scene.blend       → {blend_status}")
    print(f"{'='*60}\n")


# --------------------------------------------------------------------------- #
#  Entry point                                                                 #
# --------------------------------------------------------------------------- #

if __name__ == "__main__":
    run_pipeline(parse_args())
