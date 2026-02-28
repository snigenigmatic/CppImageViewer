cmake_minimum_required(VERSION 3.20)
project(CppImageViewer VERSION 1.0.0 LANGUAGES CXX)

# Use C++17 Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Ensure MSVC compatibility - suppress MSYS2 headers
if(MSVC)
    add_compile_options(/D_CRT_SECURE_NO_WARNINGS)
endif()

# Find Dependencies (via vcpkg toolchain)
find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)

# Add Source Files
file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.h")

# Create Executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Include Directories
target_include_directories(${PROJECT_NAME} PRIVATE src)

# Link Libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
    SDL2::SDL2main
    $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
    $<IF:$<TARGET_EXISTS:SDL2_image::SDL2_image>,SDL2_image::SDL2_image,SDL2_image::SDL2_image-static>
)

# Link Windows libraries for file dialog
if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE comdlg32)
endif()

# Copy assets to build directory (Optional convenience)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assests $<TARGET_FILE_DIR:${PROJECT_NAME}>/assests
)
