# SDF Fractal Raymarcher

A small CPU-based signed distance field (SDF) renderer written in C++, focused on rendering 3D fractals through ray marching.

The initial implementation is intentionally simple, providing a foundation for experimenting with fractal distance functions and rendering techniques.

## Features

* CPU-based SDF ray marching
* 3D fractal rendering
* Scene and scene management
* Custom minimal linear algebra library
* Runtime settings through compiler flags
* Lightweight logging namespace
* CMake build system
* tinyexr output

## Architecture

```text
Main
 |
 +-- Engine
 |    |
 |    +-- SceneManager
 |    |     |
 |    |     +-- Scene
 |    |
 |    +-- Renderer
 |         |
 |         +-- Marcher
 |
 +-- Linear Algebra
 |
 +-- Logging
```

* **Engine** - Coordinates the application and owns the SceneManager and Renderer.
* **SceneManager** - Manages scenes and the currently selected scene.
* **Scene** - Contains scene data used for rendering.
* **Renderer** - Receives the selected scene from the Engine and handles rendering.
* **Marcher** - Performs SDF ray marching and evaluates the scene.
* **Linear Algebra** - Minimal custom vector and matrix library.
* **Logging** - Lightweight logging utilities used throughout the project.

## Fractals

The primary goal of the project is exploring 3D fractal rendering using signed distance fields. Fractal distance functions can describe complex geometry without traditional polygonal meshes, making them well suited to ray marching.

## Building

Build instructions will be added as the project is finalized.

## Output

The renderer produces tinyexr images.
