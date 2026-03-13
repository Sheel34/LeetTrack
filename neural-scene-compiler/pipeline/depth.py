"""
Depth Estimation Module - Neural Scene Compiler Pipeline Stage 3

Purpose:
    Uses Intel MiDaS to produce a dense relative depth map for the input
    image.  The depth map is then used by the scene-graph module to assign
    approximate Z-coordinates to each segmented object.

    MiDaS outputs *relative* depth (not metric), which is sufficient for
    ordering objects in a 3-D scene and placing them at plausible distances.

Usage:
    python depth.py <input_image_path> [--output-dir <dir>]

Expected Output:
    - output/depth_map.png      : false-color depth visualization
    - output/depth_raw.npy      : raw float32 depth array (H x W)
    - Returns the depth array for use by scene_graph.py
"""

import argparse
import os
import sys

import cv2
import numpy as np

# PyTorch and timm are required by MiDaS
try:
    import torch
    import torch.nn.functional as F

    TORCH_AVAILABLE = True
except ImportError:
    TORCH_AVAILABLE = False


# --------------------------------------------------------------------------- #
#  Constants                                                                   #
# --------------------------------------------------------------------------- #

# MiDaS model variant — DPT_Large gives the best quality on a laptop GPU.
# Alternatives: "DPT_Hybrid", "MiDaS_small" (faster, lower quality)
DEFAULT_MIDAS_TYPE = "DPT_Large"


# --------------------------------------------------------------------------- #
#  Core functions                                                              #
# --------------------------------------------------------------------------- #

def load_midas_model(model_type: str = DEFAULT_MIDAS_TYPE,
                     device: str = "cuda"):
    """
    Download/load a MiDaS model via torch.hub.

    Args:
        model_type:  MiDaS variant identifier.
        device:      'cuda' or 'cpu'.

    Returns:
        (model, transform) — the model and its image pre-processing transform.
    """
    if not TORCH_AVAILABLE:
        raise ImportError(
            "PyTorch is not installed. Run: pip install torch torchvision"
        )

    print(f"[Depth] Loading MiDaS model ({model_type}) via torch.hub …")
    # torch.hub caches the model weights in ~/.cache/torch/hub
    model = torch.hub.load(
        "intel-isl/MiDaS", model_type, trust_repo=True
    )
    model.eval()
    model.to(device)

    # Load the matching pre-processing transform
    midas_transforms = torch.hub.load(
        "intel-isl/MiDaS", "transforms", trust_repo=True
    )
    if model_type in ("DPT_Large", "DPT_Hybrid"):
        transform = midas_transforms.dpt_transform
    else:
        transform = midas_transforms.small_transform

    print("[Depth] MiDaS model loaded.")
    return model, transform


def estimate_depth(image_bgr: np.ndarray,
                   model,
                   transform,
                   device: str = "cuda") -> np.ndarray:
    """
    Run MiDaS on an image and return a normalised depth map.

    Args:
        image_bgr:  Input image in OpenCV BGR format.
        model:      MiDaS model.
        transform:  Matching MiDaS pre-processing transform.
        device:     Compute device.

    Returns:
        float32 numpy array of shape (H, W) with values in [0, 1].
        Higher values → closer to camera (inverted convention used in
        visualisation; raw values are kept as-is for scene-graph stage).
    """
    # MiDaS expects RGB
    image_rgb = cv2.cvtColor(image_bgr, cv2.COLOR_BGR2RGB)

    input_tensor = transform(image_rgb).to(device)

    print("[Depth] Running MiDaS inference …")
    with torch.no_grad():
        prediction = model(input_tensor)
        # Resize back to original image dimensions
        prediction = F.interpolate(
            prediction.unsqueeze(1),
            size=image_bgr.shape[:2],
            mode="bicubic",
            align_corners=False,
        ).squeeze()

    depth = prediction.cpu().numpy().astype(np.float32)

    # Normalise to [0, 1] for downstream use
    d_min, d_max = depth.min(), depth.max()
    if d_max > d_min:
        depth_norm = (depth - d_min) / (d_max - d_min)
    else:
        depth_norm = np.zeros_like(depth)

    print(f"[Depth] Depth map computed.  min={d_min:.3f}  max={d_max:.3f}")
    return depth_norm


def get_object_depth(depth_map: np.ndarray, mask: np.ndarray) -> float:
    """
    Compute the median depth value for a single segmentation mask.

    Using the median rather than the mean makes the estimate robust to
    depth discontinuities at object boundaries.

    Args:
        depth_map:  Normalised depth array (H x W).
        mask:       Boolean mask (H x W) for one object.

    Returns:
        Scalar float representing relative depth (0 = far, 1 = close).
    """
    values = depth_map[mask]
    if values.size == 0:
        return 0.5  # fallback if mask is empty
    return float(np.median(values))


def save_depth_outputs(depth_map: np.ndarray, output_dir: str) -> str:
    """
    Save a false-colour depth visualisation and the raw numpy array.

    Args:
        depth_map:   Normalised float32 depth (H x W).
        output_dir:  Root output directory.

    Returns:
        Path to the saved depth_map.png file.
    """
    os.makedirs(output_dir, exist_ok=True)

    # Save raw float array for downstream modules
    raw_path = os.path.join(output_dir, "depth_raw.npy")
    np.save(raw_path, depth_map)

    # Convert to uint8 false-color image (COLORMAP_INFERNO looks great)
    depth_uint8 = (depth_map * 255).astype(np.uint8)
    depth_color = cv2.applyColorMap(depth_uint8, cv2.COLORMAP_INFERNO)

    vis_path = os.path.join(output_dir, "depth_map.png")
    cv2.imwrite(vis_path, depth_color)

    print(f"[Depth] Depth map saved to {vis_path}")
    print(f"[Depth] Raw depth array saved to {raw_path}")
    return vis_path


# --------------------------------------------------------------------------- #
#  CLI entry-point                                                             #
# --------------------------------------------------------------------------- #

def parse_args():
    parser = argparse.ArgumentParser(
        description="MiDaS depth estimation — Neural Scene Compiler Stage 3"
    )
    parser.add_argument("image", help="Path to input image")
    parser.add_argument(
        "--output-dir",
        default=os.path.join(os.path.dirname(__file__), "..", "output"),
        help="Directory to save outputs (default: ../output)",
    )
    parser.add_argument(
        "--model-type",
        default=DEFAULT_MIDAS_TYPE,
        choices=["DPT_Large", "DPT_Hybrid", "MiDaS_small"],
        help="MiDaS model variant",
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
    print(f"[Depth] Loaded image {args.image}  shape={image.shape}")

    model, transform = load_midas_model(
        model_type=args.model_type, device=args.device
    )
    depth_map = estimate_depth(image, model, transform, device=args.device)
    save_depth_outputs(depth_map, args.output_dir)

    print("\n[Depth] Done.")
    print("  Next step: run scene_graph.py to build the 3-D scene graph.")


if __name__ == "__main__":
    main()
