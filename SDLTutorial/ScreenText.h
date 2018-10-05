#pragma once
#include "Ltexture.h"
#include <sstream>

class ScreenText {
public:
    ScreenText(TTF_Font* font, SDL_Renderer* pRenderer);
    ~ScreenText();
    void setText(int iText);
    void render();
    void setText(std::string sText);

private:
    TTF_Font* m_font;
    SDL_Renderer* m_renderer;
    LTexture* m_texture;
    std::stringstream m_stream;
    std::string m_text;
};