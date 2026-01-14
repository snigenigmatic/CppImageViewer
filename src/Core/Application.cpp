#include "Application.h"
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#include <commdlg.h>
#undef LoadImage
#endif

Application::Application()
{
    m_window = std::make_unique<Window>("Cpp Modular Image Viewer", 800, 600);
}

void Application::LoadTexture(const std::string &path)
{
    m_currentImage = std::make_unique<Texture>(m_window->GetRenderer(), path);
    if (m_currentImage->IsValid())
    {
        m_currentImagePath = path;
        std::cout << "Loaded image: " << path << " (" << m_currentImage->GetWidth()
                  << "x" << m_currentImage->GetHeight() << ")" << std::endl;

        // Calculate initial zoom for "Fit to Window", preserving aspect ratio
        // Using direct scale factor relative to original image size
        float fitW = (float)m_windowWidth / m_currentImage->GetWidth();
        float fitH = (float)m_windowHeight / m_currentImage->GetHeight();

        m_zoomLevel = (fitW < fitH) ? fitW : fitH;
    }
    else
    {
        std::cerr << "Failed to load image: " << path << std::endl;
        m_currentImage.reset();
    }
}

void Application::HandleWindowResize(int newWidth, int newHeight)
{
    m_windowWidth = newWidth;
    m_windowHeight = newHeight;
}

void Application::HandleZoom(int amount)
{
    if (amount > 0)
        m_zoomLevel *= 1.1f;
    else if (amount < 0)
        m_zoomLevel /= 1.1f;

    // Clamp zoom level logic can be added here if needed
    if (m_zoomLevel < 0.1f)
        m_zoomLevel = 0.1f;
    if (m_zoomLevel > 10.0f)
        m_zoomLevel = 10.0f;
}

std::string Application::OpenFileDialog()
{
#ifdef _WIN32
    char szFile[260] = {0};
    OPENFILENAMEA ofn;
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = "Image Files\0*.jpg;*.jpeg;*.png;*.bmp;*.gif;*.tiff\0All Files\0*.*\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrTitle = "Open Image";
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    if (GetOpenFileNameA(&ofn))
    {
        return std::string(szFile);
    }
#endif
    return "";
}

void Application::Run()
{
    if (!m_window->Init())
        return;

    // Setup callbacks
    m_window->OnOpenFileRequest = [this]()
    {
        std::string path = OpenFileDialog();
        if (!path.empty())
        {
            LoadTexture(path);
        }
    };

    m_window->OnWindowResize = [this](int w, int h)
    {
        HandleWindowResize(w, h);
    };

    m_window->OnZoomRequest = [this](int amount)
    {
        HandleZoom(amount);
    };

    LoadTexture("assests/test.jpg");

    while (!m_window->IsClosed())
    {
        m_window->HandleEvents();
        m_window->Clear();

        if (m_currentImage && m_currentImage->IsValid())
        {
            // Use m_zoomLevel as direct scale factor from original resolution
            int renderWidth = (int)(m_currentImage->GetWidth() * m_zoomLevel);
            int renderHeight = (int)(m_currentImage->GetHeight() * m_zoomLevel);

            // Center
            int x = (m_windowWidth - renderWidth) / 2;
            int y = (m_windowHeight - renderHeight) / 2;

            m_currentImage->Render(m_window->GetRenderer(), x, y, renderWidth, renderHeight);
        }

        m_window->Present();
    }
}
