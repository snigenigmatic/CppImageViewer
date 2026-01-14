#include "Window.h"
#include <iostream>

Window::Window(const std::string &title, int width, int height)
    : m_title(title), m_width(width), m_height(height) {}

Window::~Window()
{
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

bool Window::Init()
{
    // Enable High DPI awareness on Windows (must be set before SDL_Init)
    SDL_SetHint(SDL_HINT_WINDOWS_DPI_AWARENESS, "permonitorv2");

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        return false;

    // Set texture filtering to "best" (anisotropic if available, else linear)
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2"))
    {
        std::cout << "Warning: Best texture filtering not enabled!" << std::endl;
    }

    // Add SDL_WINDOW_ALLOW_HIGHDPI flag
    m_window = SDL_CreateWindow(m_title.c_str(),
                                SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                m_width, m_height, 
                                SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);

    if (!m_window)
        return false;

    // Hardware accelerated renderer
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
    return m_renderer != nullptr;
}

void Window::Clear()
{
    SDL_SetRenderDrawColor(m_renderer, 30, 30, 30, 255); // Dark Grey background
    SDL_RenderClear(m_renderer);
}

void Window::Present()
{
    SDL_RenderPresent(m_renderer);
}

void Window::HandleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            m_isClosed = true;
            break;

        case SDL_WINDOWEVENT:
            if (event.window.event == SDL_WINDOWEVENT_RESIZED)
            {
                m_width = event.window.data1;
                m_height = event.window.data2;
                if (OnWindowResize)
                    OnWindowResize(m_width, m_height);
            }
            break;

        case SDL_KEYDOWN:
            if (event.key.keysym.mod & KMOD_CTRL && event.key.keysym.sym == SDLK_o)
            {
                if (OnOpenFileRequest)
                    OnOpenFileRequest();
            }
            break;

        case SDL_MOUSEWHEEL:
            if (OnZoomRequest)
                OnZoomRequest(event.wheel.y);
            break;
        }
    }
}