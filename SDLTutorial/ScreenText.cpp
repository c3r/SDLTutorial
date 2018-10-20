#include "ScreenText.h"
#include <iostream>

ScreenText::ScreenText(TTF_Font* font, SDL_Renderer* pRenderer) {
  m_renderer = pRenderer;
  m_texture = new LTexture(m_renderer);
  m_font = font;
  m_stream.str("ABCDEFGHIJKLMNOPRST");
  m_text = "ABCD";
}

ScreenText::~ScreenText() { m_texture->free(); }

void ScreenText::setText(int sScore) {
  m_stream.str("");
  m_stream << sScore;
}

void ScreenText::render() {
  SDL_Color c = {255, 255, 255, 255};
  m_texture->loadFromRenderedText(m_text.c_str(), c, m_font);
  m_texture->render(20, 20);
}

void ScreenText::setText(std::string sText) { m_text = sText; }
