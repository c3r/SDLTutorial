#include "Paddle.h"
#include <map>
#include <iostream>

Paddle::Paddle(uint16_t screenW, uint16_t screenH, LTexture* pTexture)
{
	m_posX = 0;
	m_posY = 0;

	m_velX = 0;
	m_velY = 0;

	m_pTexture = pTexture;

	m_screenHeight = screenH;
	m_screenWidth = screenW;
}

Paddle::Paddle()
{
	m_posX = 0;
	m_posY = 0;

	m_velX = 0;
	m_velY = 0;

	m_pTexture = NULL;

	m_screenHeight = 0;
	m_screenWidth = 0;
}

void Paddle::handleEvent(SDL_Event& e)
{
	static std::map<SDL_Keycode, Sint8> keymap{ {SDLK_DOWN, 5}, {SDLK_UP, -5} };

	if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
		m_velY += keymap[e.key.keysym.sym];
	}

	if (e.type == SDL_KEYUP && e.key.repeat == 0) {
		m_velY -= keymap[e.key.keysym.sym];
	}
}

void Paddle::move()
{
	m_posX += m_velX;
	if ((m_posX < 0) || (m_posX + DOT_WIDTH > m_screenWidth)) {
		m_posX -= m_velX;
	}

	m_posY += m_velY;
	if ((m_posY < 0) || (m_posY + DOT_HEIGHT > m_screenHeight)) {
		m_posY -= m_velY;
	}
}

void Paddle::render()
{
	m_pTexture->render(m_posX, m_posY);
}
