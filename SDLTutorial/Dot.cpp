#include "Dot.h"
#include <map>
#include <iostream>

Dot::Dot(uint16_t screenW, uint16_t screenH, LTexture* pTexture)
{
	m_pos_x = 0;
	m_pos_y = 0;

	m_vel_x = 0;
	m_vel_y = 0;

	m_pTexture = pTexture;

	m_screen_h = screenH;
	m_screen_w = screenW;
}

Dot::Dot()
{
	m_pos_x = 0;
	m_pos_y = 0;

	m_vel_x = 0;
	m_vel_y = 0;

	m_pTexture = NULL;

	m_screen_h = 0;
	m_screen_w = 0;
}

void Dot::handle_event(SDL_Event& e)
{
	static std::map<SDL_Keycode, Sint8> keymap{ {SDLK_DOWN, 5}, {SDLK_UP, -5} };

	if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
		m_vel_y += keymap[e.key.keysym.sym];
	}

	if (e.type == SDL_KEYUP && e.key.repeat == 0) {
		m_vel_y -= keymap[e.key.keysym.sym];
	}
}

void Dot::move()
{
	m_pos_x += m_vel_x;
	if ((m_pos_x < 0) || (m_pos_x + DOT_WIDTH > m_screen_w)) m_pos_x -= m_vel_x;

	m_pos_y += m_vel_y;
	if ((m_pos_y < 0) || (m_pos_y + DOT_WIDTH > m_screen_h)) m_pos_y -= m_vel_y; 
}

void Dot::render()
{
	m_pTexture->render(m_pos_x, m_pos_y);
}
