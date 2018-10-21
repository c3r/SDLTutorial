#include "LTexture.h"
#include <iostream>

LTexture::LTexture(SDL_Renderer *pRenderer) {
        m_renderer = pRenderer;
        m_texture = NULL;
        m_width = 0;
        m_height = 0;
}

LTexture::~LTexture() { free(); }

bool LTexture::loadFromFile(std::string path) {
        free();
        SDL_Texture *newTexture = NULL;

        SDL_Surface *loadedSurface = IMG_Load(path.c_str());
        if (loadedSurface == NULL) {
                printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(),
                        IMG_GetError());
                return false;
        }

        SDL_SetColorKey(loadedSurface, SDL_TRUE,
                SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

        newTexture = SDL_CreateTextureFromSurface(m_renderer, loadedSurface);
        if (newTexture == NULL) {
                printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(),
                        SDL_GetError());
                return false;
        }

        m_width = loadedSurface->w;
        m_height = loadedSurface->h;

        SDL_FreeSurface(loadedSurface);
        m_texture = newTexture;
        return m_texture != NULL;
}

bool LTexture::loadFromRenderedText(std::string textureText,
        SDL_Color textColor, TTF_Font *pFont) {
        free();

        SDL_Surface *textSurface =
                TTF_RenderText_Solid(pFont, textureText.c_str(), textColor);

        if (textSurface == NULL) {
                printf("Unable to render text surface! SDL_ttf Error: %s\n",
                        TTF_GetError());
                return false;
        }

        m_texture = SDL_CreateTextureFromSurface(m_renderer, textSurface);
        if (m_texture == NULL) {
                printf("Unable to create texture from rendered text! SDL Error: %s\n",
                        SDL_GetError());
                return false;
        }

        m_width = textSurface->w;
        m_height = textSurface->h;
        SDL_FreeSurface(textSurface);

        return m_texture != NULL;
}

void LTexture::free() {
        if (m_texture == NULL)
                return;

        SDL_DestroyTexture(m_texture);
        m_texture = NULL;
        m_width = 0;
        m_height = 0;
}

void LTexture::setColor(uint8_t red, uint8_t green, uint8_t blue) {
        SDL_SetTextureColorMod(m_texture, red, green, blue);
}

void LTexture::setBlendMode(SDL_BlendMode blending) {
        SDL_SetTextureBlendMode(m_texture, blending);
}

void LTexture::setAlpha(uint8_t alpha) {
        SDL_SetTextureAlphaMod(m_texture, alpha);
}

void LTexture::render(int x, int y, SDL_Rect *clip, double angle,
        SDL_Point *center, SDL_RendererFlip flip) {
        render(x, y, m_renderer, clip, angle, center, flip);
}

void LTexture::render(int x, int y, SDL_Renderer *pRenderer, SDL_Rect *clip,
        double angle, SDL_Point *center, SDL_RendererFlip flip) {
        SDL_Rect renderQuad = { x, y, m_width, m_height };
        if (clip != NULL) {
                renderQuad.w = clip->w;
                renderQuad.h = clip->h;
        }

        SDL_RenderCopyEx(pRenderer, m_texture, clip, &renderQuad, angle, center,
                flip);
}

int LTexture::getWidth() { return m_width; }

int LTexture::getHeight() { return m_height; }
