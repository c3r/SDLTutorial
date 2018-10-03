#include <map>
#include <iostream>
#include "Paddle.h"
#include "TextureManager.h"

Paddle::Paddle(std::string textureId,
	SDL_Point* pStartPos,
	uint16_t screenW,
	uint16_t screenH,
	SDL_Keycode upKey,
	SDL_Keycode downKey,
	SDL_Rect* clipRect)
{
	textureId = textureId;
	upKey = upKey;
	downKey = downKey;

	position = pStartPos;
	vel = { 0, 0 };

	scrH = screenH; // TODO: Externalize!
	scrW = screenW;

	keymap = { {downKey, Paddle::VEL}, {upKey, -Paddle::VEL} };
	clip = clipRect;
	collider = { position->x, position->y, Paddle::WIDTH, Paddle::HEIGHT };
}

Paddle::Paddle()
{
	position = new SDL_Point { 0, 0 };
	vel = { 0,0 };
	scrH = 0;
	scrW = 0;
}

void Paddle::handleEvent(SDL_Event& e)
{
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
		vel.y += keymap[e.key.keysym.sym];
	}

	if (e.type == SDL_KEYUP && e.key.repeat == 0) {
		vel.y -= keymap[e.key.keysym.sym];
	}
}

void Paddle::move()
{
	position->x += vel.x;
	collider.x = position->x;
	if ((position->x < 0) || (position->x + Paddle::WIDTH > scrW)) {
		position->x -= vel.x;
		collider.x = position->x;
	}

	position->y += vel.y;
	collider.y = position->y;
	if ((position->y < 0) || (position->y + Paddle::HEIGHT > scrH)) {
		position->y -= vel.y;
		collider.y = position->y;
	}
}

void Paddle::render(SDL_Renderer* pRenderer)
{
	SDL_SetRenderDrawColor(pRenderer, 0xFF, 0x00, 0x00, 0xFF);
	SDL_RenderFillRect(pRenderer, &collider);
}

SDL_Rect* Paddle::getCollider()
{
	return &collider;
}
