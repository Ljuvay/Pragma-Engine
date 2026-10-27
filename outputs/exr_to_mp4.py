# I DID NOT WRITE THIS, CHATGPT WROTE IT
#!/usr/bin/python3

import glob
import os
import subprocess
import sys
import tempfile
from pathlib import Path

if len(sys.argv) < 2:
    print("Usage: python3 exr_to_mp4.py <name> [fps]")
    sys.exit(1)

name = sys.argv[1]
fps = int(sys.argv[2]) if len(sys.argv) > 2 else 24

frames = sorted(glob.glob(f"{name}.*.exr"))

if len(frames) < 2:
    sys.exit(f"Not enough frames found for '{name}'.")

with tempfile.TemporaryDirectory() as temp:
    temp = Path(temp)

    for i, frame in enumerate(frames):
        output = temp / f"frame.{i:04d}.jpg"

        subprocess.run([
            "convert", frame,
            "-evaluate", "Multiply", "10.0",
            "-colorspace", "sRGB",
            str(output)
        ], check=True)

        if (i + 1) % 25 == 0 or i + 1 == len(frames):
            print(f"\rConverted {i + 1}/{len(frames)} frames", end="")

    print("\nCreating video...")

    subprocess.run([
        "ffmpeg", "-y",
        "-framerate", str(fps),
        "-i", str(temp / "frame.%04d.jpg"),
        "-c:v", "libx264",
        "-pix_fmt", "yuv420p",
        "-crf", "18",
        f"{name}.mp4"
    ], check=True)

print(f"Created {name}.mp4")
