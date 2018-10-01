#ifndef __DOT__
#define __DOT__
#include "LTexture.h"

class Dot
{
public:
	static const int DOT_WIDTH = 20;
	static const int DOT_HEIGHT = 20;
	static const int DOT_VEL = 10;

	Dot(uint16_t screenW, uint16_t screenH, LTexture* pRednerer);
	Dot();

	void handle_event(SDL_Event& e);
	void move();
	void render();

private:
	int m_pos_x, m_pos_y;
	int m_vel_x, m_vel_y;
	LTexture* m_pTexture;
	int m_screen_w, m_screen_h;
};
#endif