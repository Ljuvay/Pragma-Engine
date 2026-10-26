# SDF Fractal Raymarcher

A CPU-based 3D renderer written in C++17, exploring signed distance fields (SDFs), ray marching, and fractal rendering.

**Status: Work in Progress**

The project provides a foundation for experimenting with implicit geometry and 3D fractals, featuring a modular rendering architecture and a custom linear algebra library.

## Render Gallery

Current output from the renderer.

| Sphere | Mandelbulb |
| :----: | :--------: |
| ![Sphere render](renders/sphere.png) | ![Mandelbulb render](renders/MandelBulb.png) |

*Current renders are unshaded. The gallery will be updated as rendering capabilities develop.*

## Features

- **CPU-Based Ray Marching** — Renders implicit geometry using signed distance functions.
- **3D Fractal Rendering** — Supports fractal scene experimentation, with the Mandelbulb as a current development target.
- **Custom Linear Algebra Library** — Self-implemented vector types and mathematical operations for geometric calculations and rendering.
- **Scene Management** — Dedicated scene and scene manager components for organizing scene data.
- **Configurable Rendering Settings** — A centralized settings structure with command-line argument support.
- **EXR Image Output** — Uses [TinyEXR](https://github.com/syoyo/tinyexr) to write rendered images in OpenEXR format.
- **Logging Utilities** — Lightweight logging functionality for development and debugging.
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

- **Engine** (`src/engine/`) — Coordinates the application and connects scene management with rendering.
- **SceneManager** (`src/scene/`) — Manages scenes and tracks the currently selected scene.
- **Scene** (`src/scene/`) — Stores scene data used during rendering.
- **Renderer** (`src/renderer/`) — Coordinates the rendering process.
- **Marcher** (`src/marcher/`) — Performs ray marching and evaluates scene distance functions.
- **Linear Algebra** (`src/math/`) — Provides custom vector types and mathematical operations.
- **Settings** (`src/settings.h`) — Centralizes rendering configuration and command-line-controlled parameters.
- **Logging** (`src/logging/`) — Provides lightweight logging utilities.

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
