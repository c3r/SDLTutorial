#include "Ball.h"
#include "Paddle.h"
#include <cstdlib>

Ball::Ball(std::string textureId, SDL_Point* startingPos, uint16_t screenW, uint16_t screenH, SDL_Rect* clipRect)
{
	textureId = textureId;
	pos = startingPos;
	vel = { Ball::VEL,1 };
	screenHeight = screenH;
	screenWidth = screenW;
	clip = clipRect;
	collider = { pos->x, pos->y, Ball::WIDTH, Ball::HEIGHT };
}

Ball::~Ball()
{
}

void Ball::handleEvent(SDL_Event& e)
{

}

void Ball::move(Paddle* paddle1, Paddle* paddle2, uint32_t cTime)
{
	std::cout << "Vel: " << vel.x << ", " << vel.y << std::endl;

	pos->x += vel.x;
	collider.x = pos->x;

	if (vel.x > 0) vel = { vel.x - 0.1,  vel.y };
	if (vel.x < 0) vel = { vel.x + 0.11, vel.y };

	if (checkCollision(paddle1)) { vel.x =  Ball::VEL; }
	if (checkCollision(paddle2)) { vel.x = -Ball::VEL; }

	collider.x = pos->x;
	pos->y += vel.y;
	collider.y = pos->y;

	if ((pos->y < 0) || (pos->y + Ball::HEIGHT > screenHeight) || checkCollision(paddle1) || checkCollision(paddle2)) {
		pos->y -= vel.y;
		vel.y = -vel.y;
		collider.y = pos->y;
	}
}

bool Ball::checkCollision(Paddle* paddle)
{
	if (paddle == NULL)
		return false;

	SDL_Rect* pc = paddle->getCollider();

	int lb = collider.x, rb = collider.x + collider.w,
		tb = collider.y, bb = collider.y + collider.h;

	int lp = pc->x, rp = pc->x + pc->w,
		tp = pc->y, bp = pc->y + pc->h;

	return !(bb <= tp || tb >= bp || rb <= lp || lb >= rp);
}

void drawCircle(SDL_Renderer* pRenderer, SDL_Point* center, uint8_t radius)
{
	SDL_SetRenderDrawColor(pRenderer, 0x00, 0xFF, 0xFF, 0xFF);
	for (int w = 0; w < radius * 2; w++)
		for (int h = 0; h < radius * 2; h++)
		{
			int dx = radius - w;
			int dy = radius - h;
			if ((dx * dx + dy * dy) <= (radius * radius))
			{
				SDL_RenderDrawPoint(pRenderer, center->x + dx, center->y + dy);
			}
		}
}

void Ball::render(SDL_Renderer* pRenderer)
{
	uint8_t radius = Ball::WIDTH / 2;
	drawCircle(pRenderer, new SDL_Point{ pos->x + radius, pos->y + radius }, radius);
}

