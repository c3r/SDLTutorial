#ifndef __PADDLE__
#define __PADDLE__

#include <SDL.h>

class Paddle
{
public:
	static const int HEIGHT = 150;
	static const int WIDTH = 20;
	static const int VEL = 5;

	Paddle();

	void handleEvent(SDL_Event& e);
	void move();
	void render();

private:
	int pos;
	int vel;
};
#endif