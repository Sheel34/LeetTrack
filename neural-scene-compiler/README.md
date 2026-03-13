# Neural Scene Compiler

> **Final Year Project** — A modular computer vision pipeline that converts a
> 2D image into a structured, editable 3D scene.

---

## System Architecture

```
Input Image
    │
    ▼
┌─────────────────────┐
│  Stage 1            │  pipeline/segmentation.py
│  Segmentation (SAM) │  → per-object binary masks
└─────────────────────┘
    │
    ▼
┌─────────────────────┐
│  Stage 2            │  pipeline/classification.py
│  Classification     │  → object labels (CLIP zero-shot)
│  (CLIP)             │
└─────────────────────┘
    │
    ▼
┌─────────────────────┐
│  Stage 3            │  pipeline/depth.py
│  Depth Estimation   │  → relative depth map (MiDaS)
│  (MiDaS)            │
└─────────────────────┘
    │
    ▼
┌─────────────────────┐
│  Stage 4            │  pipeline/scene_graph.py
│  Scene Graph        │  → JSON scene representation
│  Generation         │
└─────────────────────┘
    │
    ▼
┌─────────────────────┐
│  Stage 5            │  pipeline/blender_generator.py
│  Blender Scene      │  → blender_scene.py + scene.blend
│  Generation         │
└─────────────────────┘
    │
    ▼
Editable 3D Scene
```

Each stage is **independently runnable** and **replaceable** — you can swap
SAM for another segmenter, or MiDaS for metric-depth models, without touching
any other module.

---

## Repository Structure

```
neural-scene-compiler/
│
├── data/               ← place input images here
├── models/             ← place downloaded model weights here
├── assets/             ← 3D asset files (future extension)
│
├── pipeline/
│   ├── segmentation.py         Stage 1 — SAM-based segmentation
│   ├── classification.py       Stage 2 — CLIP object classification
│   ├── depth.py                Stage 3 — MiDaS depth estimation
│   ├── scene_graph.py          Stage 4 — Scene graph JSON builder
│   └── blender_generator.py    Stage 5 — Blender scene generator
│
├── demo/
│   └── run_demo.py     End-to-end pipeline demo
│
├── output/             ← all generated outputs land here (git-ignored)
│
├── requirements.txt
└── README.md           ← you are here
```

---

## Installation

### 1. Clone the repository

```bash
git clone https://github.com/Sheel34/LeetTrack.git
cd LeetTrack/neural-scene-compiler
```

### 2. Create a Python virtual environment

```bash
python -m venv .venv
source .venv/bin/activate        # Linux / macOS
.venv\Scripts\activate           # Windows
```

### 3. Install PyTorch (with CUDA)

Choose the command that matches your CUDA version from
<https://pytorch.org/get-started/locally/>.  Example for CUDA 12.1:

```bash
pip install torch torchvision --index-url https://download.pytorch.org/whl/cu121
```

### 4. Install remaining dependencies

```bash
pip install -r requirements.txt
```

### 5. Download SAM weights

Download the ViT-H checkpoint (2.4 GB) and place it in `models/`:

```bash
mkdir -p models
wget -P models https://dl.fbaipublicfiles.com/segment_anything/sam_vit_h_4b8939.pth
```

> **Tip:** If `vit_h` is too slow for your GPU, use `vit_b` (smaller, faster)
> and pass `--sam-model-type vit_b` to the demo script.

MiDaS weights are downloaded **automatically** on first run via `torch.hub`.

---

## Quick Start

```bash
cd demo

python run_demo.py --image ../data/desk.jpg
```

### With Blender execution

Install [Blender 3.6+](https://www.blender.org/download/), then:

```bash
python run_demo.py --image ../data/desk.jpg --run-blender
```

### Run individual stages

```bash
# Stage 1 — Segmentation only
python pipeline/segmentation.py data/desk.jpg

# Stage 3 — Depth only
python pipeline/depth.py data/desk.jpg

# Stage 4 — Full pipeline up to scene graph
python pipeline/scene_graph.py data/desk.jpg

# Stage 5 — Generate Blender script from existing scene_graph.json
python pipeline/blender_generator.py --scene-graph output/scene_graph.json
```

---

## Expected Outputs

After running the demo you will find in `output/`:

| File | Description |
|------|-------------|
| `segmented_overlay.png` | Input image with coloured mask overlays |
| `masks/mask_N.png` | Individual binary mask for each object |
| `depth_map.png` | False-colour depth visualisation |
| `depth_raw.npy` | Raw float32 depth array |
| `scene_graph.json` | Structured scene representation |
| `blender_scene.py` | Auto-generated Blender Python script |
| `scene.blend` | Editable Blender scene (requires `--run-blender`) |

### Example: `scene_graph.json`

```json
{
  "objects": [
    {"id": 0, "name": "laptop",   "position": [-0.42,  0.11,  0.73]},
    {"id": 1, "name": "mug",      "position": [ 0.18, -0.05,  0.61]},
    {"id": 2, "name": "notebook", "position": [ 0.35,  0.22,  0.54]}
  ],
  "relations": [
    {"subject": "laptop", "relation": "left_of", "object": "mug"}
  ]
}
```

---

## Hardware Requirements

| Component | Minimum | Recommended |
|-----------|---------|-------------|
| GPU | NVIDIA GTX 1060 6GB | RTX 4060 / RTX 3070 |
| VRAM | 6 GB | 8–16 GB |
| RAM | 16 GB | 32 GB |
| Disk | 10 GB (models + deps) | 20 GB |

> All models run locally — no internet connection needed after installation.

---

## Technologies

| Role | Technology |
|------|-----------|
| Segmentation | [Segment Anything (SAM)](https://github.com/facebookresearch/segment-anything) |
| Classification | [OpenCLIP](https://github.com/mlfoundations/open_clip) |
| Depth estimation | [MiDaS](https://github.com/isl-org/MiDaS) via `torch.hub` |
| 3D scene generation | [Blender Python API](https://docs.blender.org/api/current/) |
| Image processing | [OpenCV](https://opencv.org/) |
| Language | Python 3.10+ |

---

## Design Principles

- **Modular** — each stage has a single responsibility and clean interface
- **Replaceable** — swap any component without breaking the rest of the pipeline
- **GPU-first** — all heavy inference runs on the local GPU; falls back to CPU
- **No training required** — all models are used zero-shot / off-the-shelf
- **Reproducible** — fixed model versions, seeded RNG, deterministic outputs

---

## Pipeline Data Flow

```
image.jpg
  │
  ├──[SAM]──────────────► masks[]          (list of binary arrays)
  │                         │
  │                    [crop regions]
  │                         │
  │         ┌───────────────┘
  │         │
  │       crops[]
  │         │
  │       [CLIP]──────────► labels[]       (name + confidence per crop)
  │
  ├──[MiDaS]────────────► depth_map        (H×W float32 array)
  │
  └──[SceneGraph]────────► scene_graph     (JSON: objects + relations)
                              │
                           [Blender]──────► scene.blend
```

---

## Next Steps / Extensions

- Replace primitive shapes with retrieved 3D assets (ShapeNet, Objaverse)
- Add metric depth via [ZoeDepth](https://github.com/isl-org/ZoeDepth) for
  real-world scale
- Support video input (process frame sequence)
- Add a simple web UI with [Gradio](https://www.gradio.app/) or
  [Streamlit](https://streamlit.io/)
