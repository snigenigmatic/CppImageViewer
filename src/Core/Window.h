#pragma once
#include <SDL2/SDL.h>
#include <string>
#include <functional>

class Window
{
public:
    Window(const std::string &title, int width, int height);
    ~Window();

    bool Init();
    void Clear();
    void Present();
    SDL_Renderer *GetRenderer() const { return m_renderer; }
    bool IsClosed() const { return m_isClosed; }
    void HandleEvents();

    int GetWidth() const { return m_width; }
    int GetHeight() const { return m_height; }

    // Callback for window resize events
    std::function<void(int, int)> OnWindowResize;
    std::function<void()> OnOpenFileRequest;
    std::function<void(int)> OnZoomRequest;

private:
    std::string m_title;
    int m_width, m_height;
    bool m_isClosed = false;

    SDL_Window *m_window = nullptr;
    SDL_Renderer *m_renderer = nullptr;
};