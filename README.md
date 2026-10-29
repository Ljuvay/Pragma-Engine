# Pragma Engine

A CPU-based rendering engine built around signed distance field (SDF) ray marching, procedural fractals, and multithreaded tile-based rendering.

Developed as an alternative project for **CPSC 3220: Operating Systems** at Clemson University, this project explores CPU parallelism through tile-based rendering, static and dynamic work scheduling, and runtime comparisons across different worker counts.

## Renders

### Mandelbulb

![Mandelbulb render](renders/MandelBulbColor.png)

[Watch Mandelbulb Animation](https://youtu.be/9kWrbisHZGk)

### Fractal Tower

![Fractal Tower render](renders/FractalTowerColor.png)

[Watch Fractal Tower Animation](https://youtu.be/TRJZj_DH--o)

Both fractal scenes use **depth-based shading** derived from ray-marching step counts rather than traditional lighting.

### Sphere

![Sphere render](renders/sphere.png)

The sphere scene demonstrates basic SDF surface rendering without surface lighting.

## Features

- **CPU Ray Marching:** Renders procedural scenes using signed distance functions.
- **Procedural Fractals:** Includes a Mandelbulb and a Fractal Tower, alongside a sphere scene.
- **Tile-Based Rendering:** Divides the image into tiles for independent processing.
- **Multithreaded Execution:** Configurable worker count using the C++ standard threading library.
- **Static Scheduling:** Assigns tiles to workers using a strided distribution.
- **Dynamic Scheduling:** Workers claim the next available tile using an atomic counter.
- **Configurable Rendering:** Adjust image resolution, frame count, ray-marching parameters, thread count, and tile-grid resolution through command-line arguments.
- **Animated Rendering:** Supports rendering scenes across multiple frames.
- **EXR Output:** Writes rendered frames as EXR images.
- **Runtime Logging:** Measures scheduler and frame-output durations.
- **Modular Architecture:** Separates scene evaluation, ray marching, rendering, scheduling, and engine management.

## Shading

Pragma Engine uses depth-based shading rather than physically based lighting. Surface colors are determined by ray-marching step counts and, for some scenes, hit position.

- **Mandelbulb:** Uses ray-marching depth and hit position to produce color variation.
- **Fractal Tower:** Uses grayscale shading based on ray-marching depth.
- **Sphere:** Displays a basic red SDF sphere without surface lighting.
- **Misses:** Each scene defines its own background color.
- **Maximum-step exhaustion:** Rays that reach the maximum iteration count without hitting a surface are displayed in red.

This approach provides visual depth cues while keeping the shading implementation focused on the ray marcher itself.

## Parallel Rendering

Rendering is divided into a configurable grid of tiles that can be processed by multiple worker threads.

### Static Scheduling

Each worker processes a strided sequence of tile indices. Work assignment is determined by the scheduler, and workers render their assigned tiles independently.

### Dynamic Scheduling

Workers use an atomic counter to claim tiles as they become available. Each worker continues processing until all tiles have been claimed.

Both schedulers use the same underlying ray marcher and scene implementation, allowing their performance to be compared under equivalent rendering settings.

### Preliminary Benchmark

Preliminary testing was performed on Clemson's Ada4 computing environment using full application runtime.

| Configuration | Total runtime |
|---|---:|
| 1 thread, static scheduling | 195.443 s |
| 3 threads, static scheduling | 80.738 s |

Increasing the worker count from one to three achieved an observed **2.42× speedup**, reducing total runtime by approximately **58.7%**.

These results are preliminary measurements from one run per configuration. Both runs used static scheduling, so the comparison examines the effect of increasing the worker count under the tested conditions.

## Architecture

```text
Main
└── Engine
    ├── SceneManager
    │   └── Scene
    │       ├── SDF Evaluation
    │       ├── Shading
    │       └── Camera
    │
    └── Renderer
        ├── Tile Scheduler
        │   ├── Static Scheduling
        │   └── Dynamic Scheduling
        ├── Worker Threads
        ├── Ray Marcher
        └── Frame Buffer
            └── EXR Output
```

### Core Components

| Component | Responsibility |
|---|---|
| `Engine` | Coordinates application execution and frame rendering. |
| `SceneManager` | Manages the active rendering scene. |
| `Scene` | Defines SDF evaluation, shading, and camera behavior. |
| `Renderer` | Builds tiles, schedules work, and manages the frame buffer. |
| `RayMarcher` | Traces rays and evaluates their intersections with SDF surfaces. |
| `Math` | Provides custom linear algebra utilities. |
| `Logging` | Records scheduler and frame-output timings. |

## Built With

- **C++20**
- **CMake**
- **C++ Standard Library Threads**
- **TinyEXR** for EXR output

## Tested Environments

- Windows — Microsoft Visual Studio 2022
- Linux — Clemson Ada4

## Building and Running

### Linux

From the project root:

```bash
mkdir build
cd build
cmake ..
make
```

Run the executable from the build directory:

```bash
./RayMarchingFractals
```

Enable runtime logging:

```bash
./RayMarchingFractals -logging
```

### Windows

The project can be configured and built using CMake with Microsoft Visual Studio 2022.

## Command-Line Options

All options are optional and use the defaults listed below.

| Argument | Default | Description |
|---|---|---|
| `-w` | `1920` | Output image width. |
| `-h` | `1080` | Output image height. |
| `-fName` | `output` | Output directory and filename prefix. |
| `-scene` | `MandelBulbScene` | Scene to render. |
| `-frames` | `24` | Number of frames to render. |
| `-steps` | `2500` | Maximum ray-marching steps. |
| `-near` | `0.01` | Near ray-marching distance. |
| `-far` | `100` | Maximum ray-marching distance. |
| `-epsilon` | `0.0001` | Surface-hit tolerance. |
| `-threads` | `1` | Number of worker threads. |
| `-tres` | `16` | Tile-grid resolution per dimension. |
| `-dynamic` | Disabled | Enables dynamic tile scheduling. |
| `-logging` | Disabled | Enables runtime timing logs. |

The tile-grid resolution determines the number of tiles per dimension. For example, `-tres 16` creates up to 256 tiles.

### Examples

Render with three worker threads using static scheduling:

```bash
./RayMarchingFractals -threads 3
```

Render with three worker threads using dynamic scheduling:

```bash
./RayMarchingFractals -threads 3 -dynamic
```

Enable runtime logging:

```bash
./RayMarchingFractals -logging
```

Select a scene using the `-scene` argument:

```bash
./RayMarchingFractals -scene SphereScene
./RayMarchingFractals -scene MandelBulbScene
./RayMarchingFractals -scene FractalTowerScene
```

Customize output resolution and frame count:

```bash
./RayMarchingFractals -w 1920 -h 1080 -frames 24
```

## Output

Rendered frames are written as numbered EXR files:

```text
outputs/
└── <name>/
    ├── <name>.0000.exr
    ├── <name>.0001.exr
    └── ...
```

The `outputs/exr_to_mp4.py` helper script can convert a sequence of rendered EXR frames into a video.

## Project Structure

```text
Pragma-Engine/
├── main.cpp
├── CMakeLists.txt
├── CMakePresets.json
├── src/
│   ├── engine/
│   ├── logging/
│   ├── marcher/
│   ├── math/
│   ├── renderer/
│   ├── scene/
│   └── settings.h
├── renders/
│   ├── MandelBulbColor.png
│   ├── MandelBulb.mp4
│   ├── FractalTowerColor.png
│   ├── FractalTower.mp4
│   └── sphere.png
└── outputs/
    └── exr_to_mp4.py
```

## Author

**Dylan Kauffman**

GitHub: [Ljuvay](https://github.com/Ljuvay)
