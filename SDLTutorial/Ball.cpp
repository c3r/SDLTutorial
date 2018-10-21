#include "Ball.h"
#include <cstdlib>
#include "Paddle.h"

Ball::Ball(SDL_Point *startingPos, SDL_Rect *tableRect) {
	pos = startingPos;
	vel = { Ball::VEL, 2 };
	this->tableRect = tableRect;
	collider = { pos->x, pos->y, Ball::WIDTH, Ball::HEIGHT };
}

Ball::~Ball() {}

void Ball::handleEvent(SDL_Event &e) {}

bool Ball::checkForScore(Paddle *lp, Paddle *rp) {
	if (pos->x < tableRect->x) {
		handleScore(rp, lp);
		return true;
	}
	if (pos->x + Ball::WIDTH > (tableRect->x + tableRect->w)) {
		handleScore(lp, rp);
		return true;
	}
	return false;
}

void Ball::handleScore(Paddle *scoring, Paddle *serving) {
	scoring->addPoint();
	stickTo(serving);
	vel = { 0, 0 };
}

void Ball::unstick(Paddle *p) {
	vel.x = p->getServeDirection() * Ball::VEL;
	stickingPaddle = nullptr;
}

void Ball::move(Paddle *lp, Paddle *rp) {
	if (stickToPaddle()) { return; }

	// Move
	collider.x = pos->x += vel.x;  // Move in x axis
	collider.y = pos->y += vel.y;  // Move in Y axis

	// Check for score
	if (checkForScore(lp, rp)) { return; }

	// Check for collisions
	if (collision(lp)) { collide(lp); return; }
	if (collision(rp)) { collide(rp); return; }

	// Wall collision
	if ((pos->y <= tableRect->y) || (pos->y + Ball::HEIGHT > tableRect->y + tableRect->h)) {
		pos->y -= vel.y;
		vel.y = -vel.y;
		collider.y = pos->y;
	}
}

bool Ball::stickToPaddle() {
	if (stickingPaddle == nullptr) { return false; }

	SDL_Point *pmp = stickingPaddle->getMiddlePoint();
	int dir = stickingPaddle->getServeDirection();

	pos->x = pmp->x + dir * (Paddle::WIDTH / 2 + Ball::WIDTH / 2) - Ball::WIDTH / 2;
	pos->y = pmp->y - Ball::WIDTH / 2;

	return true;
}

void Ball::collide(Paddle *cp) {
	if (cp == nullptr) { return; }

	// If ball and paddle are coming in the same direction, return.
	// This prevents of multiple collisions when the paddle is coming
	// the same way that the ball is after collision.
	if (cp->getServeDirection() * vel.x > 0) { return; }

	// abs
	if (vel.x < 0) { vel.x *= -1; }

	vel.x = cp->getServeDirection() * abs(vel.x) + cp->getVel()->x / 1.5;
	vel.y = vel.y - cp->getVel()->y / 2.5;
	std::cout << vel.x << ", " << vel.y << std::endl;
}

bool Ball::collision(Paddle *paddle) {
	if (paddle == nullptr) { return false; }

	SDL_Rect *pc = paddle->getCollider();

	int lb = collider.x,
		rb = collider.x + collider.w,
		tb = collider.y,
		bb = collider.y + collider.h;

	int lp = pc->x,
		rp = pc->x + pc->w,
		tp = pc->y,
		bp = pc->y + pc->h;

	return !(bb <= tp || tb >= bp || rb <= lp || lb >= rp);
}

void drawCircle(SDL_Renderer *pRenderer, SDL_Point *center, uint8_t radius) {
	SDL_SetRenderDrawColor(pRenderer, 0xEE, 0xE0, 0x93, 0xFF);
	for (int w = 0; w < radius * 2; w++)
		for (int h = 0; h < radius * 2; h++) {
			int dx = radius - w;
			int dy = radius - h;
			if ((dx * dx + dy * dy) <= (radius * radius)) {
				SDL_RenderDrawPoint(pRenderer, center->x + dx, center->y + dy);
			}
		}
}

void Ball::render(SDL_Renderer *pRenderer) {
	uint8_t radius = Ball::WIDTH / 2;
	drawCircle(pRenderer, new SDL_Point{ pos->x + radius, pos->y + radius }, radius);
}

void Ball::stickTo(Paddle *paddle) {
	paddle->stick(this);
	stickingPaddle = paddle;
}
