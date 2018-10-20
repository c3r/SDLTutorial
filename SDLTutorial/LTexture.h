#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>

class TextureManager;
class LTexture {
 public:
  LTexture(SDL_Renderer* renderer);
  ~LTexture();

  bool loadFromFile(std::string path);
  bool loadFromRenderedText(std::string textureText, SDL_Color textColor,
                            TTF_Font* pFont);
  void setColor(uint8_t red, uint8_t green, uint8_t blue);
  void setBlendMode(SDL_BlendMode blending);
  void setAlpha(uint8_t alpha);
  void free();

  void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0,
              SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

  void render(int x, int y, SDL_Renderer* pRenderer, SDL_Rect* clip = NULL,
              double angle = 0.0, SDL_Point* center = NULL,
              SDL_RendererFlip flip = SDL_FLIP_NONE);

  int getWidth();
  int getHeight();

 private:
  SDL_Texture* m_texture;
  SDL_Renderer* m_renderer;
  int m_width;
  int m_height;
};
