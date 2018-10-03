#pragma once
#include "TextureManager.h"
#include "Paddle.h"
#include "Geometry.h"
#include <string>

class Ball
{
public:

	static const int WIDTH = 20;
	static const int HEIGHT = 20;
	static const int VEL = 12;

	Ball(std::string textureId, SDL_Point* startingPos, uint16_t screenW, uint16_t screenH, SDL_Rect* clipRect);
	~Ball();

	void handleEvent(SDL_Event& e);
	void move(Paddle* paddle1, Paddle* paddle2, uint32_t cTime);
	bool checkCollision(Paddle* paddle);
	void render(SDL_Renderer* renderer);

private:
	std::string textureId;
	SDL_Point* pos;
	Velocity vel;
	int screenWidth, screenHeight;
	SDL_Rect* clip;
	SDL_Rect collider;
};


