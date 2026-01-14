# C++ Image Viewer

A simple image viewer built with C++17 and SDL2.

## Quick Start

1. **Clone**:
   ```bash
   git clone --recurse-submodules https://github.com/snigenigmatic/CppImageViewer.git
   ```

2. **Build**:
   ```bash
   cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=vcpkg/scripts/buildsystems/vcpkg.cmake
   cmake --build build --config Release
   ```

3. **Run**:
   ```bash
   ./build/Release/CppImageViewer.exe
   ```

## Controls
- **Ctrl + O**: Open Image
- **Mouse Wheel**: Zoom In/Out
