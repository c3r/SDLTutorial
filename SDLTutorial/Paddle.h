#ifndef __PADDLE__
#define __PADDLE__
#include "LTexture.h"

class Paddle
{
public:
	static const int DOT_WIDTH = 20;
	static const int DOT_HEIGHT = 20;
	static const int DOT_VEL = 10;

	Paddle(uint16_t screenW, uint16_t screenH, LTexture* pRednerer);
	Paddle();

	void handleEvent(SDL_Event& e);
	void move();
	void render();

private:
	int m_posX, m_posY;
	int m_velX, m_velY;
	LTexture* m_pTexture;
	int m_screenWidth, m_screenHeight;
};
#endif