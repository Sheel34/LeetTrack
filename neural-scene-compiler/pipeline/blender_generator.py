"""
Blender Scene Generator - Neural Scene Compiler Pipeline Stage 5

Purpose:
    Reads the scene graph JSON produced by scene_graph.py and generates a
    Blender Python script that, when executed inside Blender, creates a 3-D
    scene with:
        - A ground plane
        - Simple primitive objects (cubes / UV spheres) placed at the
          positions specified by the scene graph
        - Object names matching the classification labels
        - A camera and three-point lighting rig

    This module generates a .py script that you run inside Blender, OR
    it can call Blender directly via subprocess if Blender is installed.

Usage:
    # Generate the Blender script only:
    python blender_generator.py --scene-graph output/scene_graph.json

    # Generate script AND execute Blender (if installed):
    python blender_generator.py --scene-graph output/scene_graph.json --run-blender

Expected Output:
    - output/blender_scene.py   : Blender Python script
    - output/scene.blend        : Blender file (only if --run-blender is set)
"""

import argparse
import json
import os
import subprocess
import sys
import textwrap


# --------------------------------------------------------------------------- #
#  Constants                                                                   #
# --------------------------------------------------------------------------- #

# Scale factor: convert normalised [-1, 1] coords to Blender units (metres)
SCENE_SCALE = 3.0

# Default vertical position of all objects (resting on the ground plane)
GROUND_Y = 0.5   # half the default cube height


# --------------------------------------------------------------------------- #
#  Script template builders                                                    #
# --------------------------------------------------------------------------- #

def _object_primitive(name: str, x: float, y: float, z: float) -> str:
    """
    Return a Blender-Python snippet that adds a primitive for one object.

    Objects starting with 'person' or 'plant' get a UV sphere;
    everything else gets a cube.
    """
    shape = (
        "bpy.ops.mesh.primitive_uv_sphere_add"
        if name.lower() in ("person", "plant", "cat", "dog")
        else "bpy.ops.mesh.primitive_cube_add"
    )
    return textwrap.dedent(f"""\
        # Object: {name}
        {shape}(location=({x:.4f}, {z:.4f}, {GROUND_Y:.4f}))
        obj = bpy.context.active_object
        obj.name = "{name}"
        obj.data.name = "{name}_mesh"
        mat = bpy.data.materials.new(name="{name}_mat")
        mat.use_nodes = True
        obj.data.materials.append(mat)
    """)


def build_blender_script(scene_graph: dict, blend_output_path: str) -> str:
    """
    Generate the full Blender Python script as a string.

    Args:
        scene_graph:        Dict from scene_graph.py (objects + relations).
        blend_output_path:  Absolute path where Blender should save scene.blend.

    Returns:
        String containing the complete Blender Python script.
    """
    # --- Header ---
    lines = [
        "import bpy",
        "import math",
        "",
        "# ---- Neural Scene Compiler — auto-generated scene ----",
        "",
        "# Clear default scene",
        "bpy.ops.wm.read_factory_settings(use_empty=True)",
        "",
    ]

    # --- Ground plane ---
    lines += [
        "# Ground plane",
        "bpy.ops.mesh.primitive_plane_add(size=20, location=(0, 0, 0))",
        "ground = bpy.context.active_object",
        "ground.name = 'Ground'",
        "",
    ]

    # --- Objects ---
    lines.append("# --- Scene objects ---")
    for obj in scene_graph.get("objects", []):
        name = obj["name"].replace(" ", "_")
        px, py, pz = obj["position"]
        # Map normalised coords to Blender units
        bx = px * SCENE_SCALE
        bz = -py * SCENE_SCALE   # y in image coords → -z in Blender top-down
        bz_depth = pz * SCENE_SCALE
        lines.append(_object_primitive(name, bx, bz_depth, bz))

    # --- Camera ---
    lines += [
        "# Camera",
        "bpy.ops.object.camera_add(location=(0, -10, 5))",
        "cam = bpy.context.active_object",
        "cam.rotation_euler = (math.radians(60), 0, 0)",
        "bpy.context.scene.camera = cam",
        "",
    ]

    # --- Three-point lighting ---
    lines += [
        "# Key light",
        "bpy.ops.object.light_add(type='SUN', location=(5, -5, 10))",
        "bpy.context.active_object.data.energy = 3.0",
        "",
        "# Fill light",
        "bpy.ops.object.light_add(type='AREA', location=(-5, -5, 5))",
        "bpy.context.active_object.data.energy = 1.0",
        "",
        "# Back light",
        "bpy.ops.object.light_add(type='SPOT', location=(0, 5, 8))",
        "bpy.context.active_object.data.energy = 2.0",
        "",
    ]

    # --- Save .blend file ---
    # Escape backslashes for Windows paths
    safe_path = blend_output_path.replace("\\", "\\\\")
    lines += [
        f'# Save scene',
        f'bpy.ops.wm.save_as_mainfile(filepath="{safe_path}")',
        f'print("[Blender] Scene saved to {safe_path}")',
    ]

    return "\n".join(lines) + "\n"


def save_blender_script(script: str, output_dir: str) -> str:
    """
    Write the generated script to disk.

    Returns:
        Path to the saved .py file.
    """
    os.makedirs(output_dir, exist_ok=True)
    script_path = os.path.join(output_dir, "blender_scene.py")
    with open(script_path, "w", encoding="utf-8") as fh:
        fh.write(script)
    print(f"[Blender] Script saved to {script_path}")
    return script_path


def run_blender(script_path: str,
                blender_executable: str = "blender") -> int:
    """
    Execute the generated script inside Blender (background mode).

    Args:
        script_path:         Path to the .py Blender script.
        blender_executable:  Path to the Blender binary (default: 'blender').

    Returns:
        Subprocess return code (0 = success).
    """
    cmd = [
        blender_executable,
        "--background",
        "--python", script_path,
    ]
    print(f"[Blender] Running: {' '.join(cmd)}")
    result = subprocess.run(cmd, capture_output=False)
    if result.returncode != 0:
        print(
            f"[Blender] Blender exited with code {result.returncode}.",
            file=sys.stderr,
        )
    return result.returncode


# --------------------------------------------------------------------------- #
#  CLI entry-point                                                             #
# --------------------------------------------------------------------------- #

def parse_args():
    parser = argparse.ArgumentParser(
        description="Blender scene generator — Neural Scene Compiler Stage 5"
    )
    parser.add_argument(
        "--scene-graph",
        default=os.path.join(
            os.path.dirname(__file__), "..", "output", "scene_graph.json"
        ),
        help="Path to scene_graph.json produced by scene_graph.py",
    )
    parser.add_argument(
        "--output-dir",
        default=os.path.join(os.path.dirname(__file__), "..", "output"),
        help="Directory to save blender_scene.py and scene.blend",
    )
    parser.add_argument(
        "--run-blender",
        action="store_true",
        help="Execute Blender after generating the script",
    )
    parser.add_argument(
        "--blender-executable",
        default="blender",
        help="Path to Blender binary (default: 'blender')",
    )
    return parser.parse_args()


def main():
    args = parse_args()

    if not os.path.exists(args.scene_graph):
        print(
            f"[Error] Scene graph not found: {args.scene_graph}\n"
            "        Run scene_graph.py first.",
            file=sys.stderr,
        )
        sys.exit(1)

    with open(args.scene_graph, "r", encoding="utf-8") as fh:
        scene_graph = json.load(fh)

    n_objects = len(scene_graph.get("objects", []))
    print(f"[Blender] Loaded scene graph with {n_objects} objects.")

    blend_path = os.path.abspath(
        os.path.join(args.output_dir, "scene.blend")
    )
    script = build_blender_script(scene_graph, blend_path)
    script_path = save_blender_script(script, args.output_dir)

    if args.run_blender:
        rc = run_blender(script_path, args.blender_executable)
        if rc == 0:
            print(f"\n[Blender] scene.blend saved to {blend_path}")
    else:
        print(
            "\n[Blender] Script generated.  To create the .blend file run:\n"
            f"  blender --background --python {script_path}"
        )

    print("\n[Blender] Pipeline complete.")
    print(
        "  Outputs:\n"
        f"    segmented_overlay.png  → {os.path.join(args.output_dir, 'segmented_overlay.png')}\n"
        f"    depth_map.png          → {os.path.join(args.output_dir, 'depth_map.png')}\n"
        f"    scene_graph.json       → {os.path.join(args.output_dir, 'scene_graph.json')}\n"
        f"    blender_scene.py       → {script_path}\n"
        f"    scene.blend            → {blend_path} (requires Blender)"
    )


if __name__ == "__main__":
    main()
