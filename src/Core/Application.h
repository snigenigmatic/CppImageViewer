#pragma once
#include "Window.h"
#include "../Graphics/Texture.h"
#include <memory>
#include <string>

class Application
{
public:
    Application();
    void Run();

private:
    std::unique_ptr<Window> m_window;
    std::unique_ptr<Texture> m_currentImage;
    std::string m_currentImagePath;
    int m_windowWidth = 800;
    int m_windowHeight = 600;
    float m_zoomLevel = 1.0f;

    void LoadTexture(const std::string &path);
    void HandleWindowResize(int newWidth, int newHeight);
    void HandleZoom(int amount);
    std::string OpenFileDialog();
};