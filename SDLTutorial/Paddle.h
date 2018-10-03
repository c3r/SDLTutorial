#pragma once
#include "LTexture.h"
#include <map>

class Paddle
{
public:
	static const int WIDTH = 15;
	static const int HEIGHT = 100;
	static const int VEL = 3;

	Paddle(std::string textureId, 
		SDL_Point* startPos,
		uint16_t screenW, 
		uint16_t screenH, 
		SDL_Keycode upKey, 
		SDL_Keycode downKey,
		SDL_Rect* clipRect);

	Paddle();

	void handleEvent(SDL_Event& e);
	void move();
	void render(SDL_Renderer* renderer);
	SDL_Rect* getCollider();

private:
	SDL_Keycode upKey, downKey;
	std::string textureId;
	SDL_Point* position;
	SDL_Point vel;
	int scrW, scrH;
	std::map<SDL_Keycode, Sint8> keymap;
	SDL_Rect* clip;
	SDL_Rect collider;
};