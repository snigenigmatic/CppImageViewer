#include "Texture.h"
#include <iostream>

Texture::Texture(SDL_Renderer *renderer, const std::string &path)
{
  SDL_Surface *surface = IMG_Load(path.c_str());
  if (!surface)
  {
    std::cerr << "Failed to load image: " << IMG_GetError() << std::endl;
    return;
  }
  m_texture = SDL_CreateTextureFromSurface(renderer, surface);
  
  // Explicitly set scale mode to best (requires SDL 2.0.12+)
  SDL_SetTextureScaleMode(m_texture, SDL_ScaleModeBest);

  m_width = surface->w;
  m_height = surface->h;

  SDL_FreeSurface(surface);
}

Texture::~Texture()
{
  if (m_texture)
  {
    SDL_DestroyTexture(m_texture);
  }
}

void Texture::Render(SDL_Renderer *renderer, int x, int y)
{
  if (!m_texture)
    return;

  SDL_Rect dstRect = {x, y, m_width, m_height};
  SDL_RenderCopy(renderer, m_texture, nullptr, &dstRect);
}

void Texture::Render(SDL_Renderer *renderer, int x, int y, int w, int h)
{
  if (!m_texture)
    return;

  SDL_Rect dstRect = {x, y, w, h};
  SDL_RenderCopy(renderer, m_texture, nullptr, &dstRect);
}

void Texture::RenderScaled(SDL_Renderer *renderer, int destWidth, int destHeight)
{
  if (!m_texture)
    return;

  // Calculate aspect ratio
  float imageAspect = (float)m_width / m_height;
  float windowAspect = (float)destWidth / destHeight;

  int renderWidth, renderHeight;
  if (imageAspect > windowAspect)
  {
    // Image is wider, fit to width
    renderWidth = destWidth;
    renderHeight = (int)(destWidth / imageAspect);
  }
  else
  {
    // Image is taller, fit to height
    renderHeight = destHeight;
    renderWidth = (int)(destHeight * imageAspect);
  }

  // Center the image
  int x = (destWidth - renderWidth) / 2;
  int y = (destHeight - renderHeight) / 2;

  SDL_Rect dstRect = {x, y, renderWidth, renderHeight};
  SDL_RenderCopy(renderer, m_texture, nullptr, &dstRect);
}