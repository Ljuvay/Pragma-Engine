# Pragma Engine

A small, CPU-based rendering engine written in C++17, built around signed distance fields (SDFs), ray marching, and 3D fractal rendering.

**Status: Work in Progress**

Pragma Engine is a personal graphics programming project exploring the foundations of a modular rendering system, with a focus on implicit geometry and procedural 3D fractals.

## Render Gallery

Current output from the renderer.

| Sphere | Mandelbulb |
| :---: | :---: |
| ![Sphere render](renders/sphere.png) | ![Mandelbulb render](renders/MandelBulb.png) |

*Current renders are unshaded. The renderer is under active development.*

## Features

- **CPU-Based Ray Marching** — Renders implicit geometry using signed distance functions.
- **3D Fractal Rendering** — Supports experimentation with procedural fractal geometry, with the Mandelbulb as a current development target.
- **Modular Engine Architecture** — Separates application logic, scene management, rendering, and ray marching into dedicated components.
- **Custom Linear Algebra Library** — Implements custom vector types and mathematical operations for geometric calculations.
- **Scene Management** — Uses dedicated scene and scene manager components to organize scene data and track the active scene.
- **Configurable Rendering Settings** — Centralizes rendering parameters and supports command-line configuration.
- **EXR Image Output** — Uses [TinyEXR](https://github.com/syoyo/tinyexr) to write rendered images in OpenEXR format.
- **Logging Utilities** — Provides lightweight logging functionality for development and debugging.
- **CMake Build System** — Uses CMake and CMake Presets for build configuration.

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
 +-- Settings
 |
 +-- Linear Algebra
 |
 +-- Logging
```

### Components

| Component | Responsibility |
|---|---|
| `Engine` (`src/engine/`) | Coordinates application execution and connects scene management with rendering. |
| `SceneManager` (`src/scene/`) | Manages scenes and tracks the currently selected scene. |
| `Scene` (`src/scene/`) | Stores scene data used during rendering. |
| `Renderer` (`src/renderer/`) | Coordinates the rendering process. |
| `Marcher` (`src/marcher/`) | Performs ray marching and evaluates scene distance functions. |
| `Linear Algebra` (`src/math/`) | Provides custom vector types and mathematical operations. |
| `Settings` (`src/settings.h`) | Centralizes rendering configuration and command-line-controlled parameters. |
| `Logging` (`src/logging/`) | Provides lightweight logging utilities. |

## Technologies

- **Language:** C++17
- **Build System:** CMake
- **Build Configuration:** CMake Presets
- **Rendering:** CPU-based SDF ray marching
- **Mathematics:** Custom linear algebra library
- **Image Output:** [TinyEXR](https://github.com/syoyo/tinyexr) / OpenEXR

## Building

Build instructions will be added as cross-platform testing progresses.

## Platform Support

- **Windows:** Tested.
- **Linux:** Not yet tested.

## Author

Developed by [Ljuvay](https://github.com/Ljuvay).
