#pragma once
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Texture
{
public:
  Texture(SDL_Renderer *renderer, const std::string &path);
  ~Texture();

  void Render(SDL_Renderer *renderer, int x, int y);
  void Render(SDL_Renderer *renderer, int x, int y, int w, int h);
  void RenderScaled(SDL_Renderer *renderer, int destWidth, int destHeight);
  int GetWidth() const { return m_width; }
  int GetHeight() const { return m_height; }
  bool IsValid() const { return m_texture != nullptr; }

private:
  SDL_Texture *m_texture = nullptr;
  int m_width = 0;
  int m_height = 0;
};
