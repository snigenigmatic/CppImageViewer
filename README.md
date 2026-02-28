# C++ Image Viewer

A lightweight image viewer built with C++17, SDL2, and SDL2_image.

## Features

- Open images via native Windows file dialog (Ctrl+O)
- Zoom in/out with mouse wheel
- Automatic fit-to-window on load and resize
- High DPI support
- JPEG and PNG support (via libjpeg-turbo and libpng)

## Prerequisites

- [CMake](https://cmake.org/) 3.20+
- [Ninja](https://ninja-build.org/) build system
- [LLVM/Clang](https://llvm.org/) (clang-cl)
- Visual Studio 2022 (for MSVC libs and Windows SDK)

## Quick Start

1. **Clone** (with vcpkg submodule):
   ```bash
   git clone --recurse-submodules https://github.com/snigenigmatic/CppImageViewer.git
   cd CppImageViewer
   ```

2. **Configure and build** using the CMake preset:
   ```bash
   cmake --preset Clang-cl
   cmake --build build
   ```

   Or manually:
   ```bash
   cmake -S . -B build -G Ninja -DCMAKE_CXX_COMPILER="C:/Program Files/LLVM/bin/clang-cl.exe" -DCMAKE_TOOLCHAIN_FILE=vcpkg/scripts/buildsystems/vcpkg.cmake
   cmake --build build
   ```

3. **Run**:
   ```bash
   ./build/CppImageViewer.exe
   ```

## Controls

- **Ctrl + O** — Open image
- **Mouse Wheel** — Zoom in/out

## Project Structure

```
src/
├── main.cpp              # Entry point
├── Core/
│   ├── Application.cpp   # App logic, zoom, file dialog
│   ├── Application.h
│   ├── Window.cpp        # SDL2 window/renderer management
│   └── Window.h
└── Graphics/
    ├── Texture.cpp       # Image loading and rendering
    └── Texture.h
```
