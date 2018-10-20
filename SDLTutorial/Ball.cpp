#include "Ball.h"
#include "Paddle.h"
#include <cstdlib>
#include <cmath>

Ball::Ball(std::string textureId,
    SDL_Point* startingPos,
    uint16_t screenW,
    uint16_t screenH,
    SDL_Rect* clipRect)
{
    textureId = textureId;
    pos = startingPos;
    vel = { Ball::VEL, 2 };
    screenHeight = screenH;
    screenWidth = screenW;
    clip = clipRect;
    collider = { pos->x, pos->y, Ball::WIDTH, Ball::HEIGHT };
}

Ball::~Ball() {}

void Ball::handleEvent(SDL_Event& e)
{
}

void Ball::checkForScore(Paddle* lp, Paddle* rp)
{	
	if (pos->x + Ball::WIDTH < 0)
		handleScore(rp, lp);
	
	if (pos->x - Ball::WIDTH > screenWidth)
		handleScore(lp, rp);	
}

void Ball::handleScore(Paddle* scoring, Paddle* serving)
{
	scoring->addPoint();
	serving->stick(this);
	vel = { 0, 0 };
}

void Ball::unstick(Paddle* p)
{
    vel.x = p->getServeDirection() * Ball::VEL;
    //m_vel.y = SDL_GetTicks() % 2 == 0 ? -2 : 2; // TODO: zrobic to jakos lepiej, lol
}

void Ball::move(Paddle* lp, Paddle* rp)
{
    if (lp->isBallSticking(this)) {
        pos = new SDL_Point { 
            lp->getPosition()->x + Paddle::WIDTH,
            lp->getPosition()->y + Paddle::HEIGHT / 2 };
        return;
    }

    if (rp->isBallSticking(this)) {
        pos = new SDL_Point { 
            rp->getPosition()->x - Ball::WIDTH,
            rp->getPosition()->y + Paddle::HEIGHT / 2 };
        return;
    }

    // TODO: zrobic zwalnianie tak zeby to mialo sens i bylo SYMETRYCZNE
    // deaccelerate
    // if (m_vel.x > 0.08) {
    //     m_vel = { m_vel.x - 0.105, m_vel.y };
    // }
    // if (m_vel.x < -0.08) {
    //     m_vel = { m_vel.x + 0.11, m_vel.y };
    // }

    // Move
    collider.x = pos->x += vel.x; // Move in x axis
    collider.y = pos->y += vel.y; // Move in Y axis

    // Check for score
    checkForScore(lp, rp);

    // Check for collisions
    if (collision(lp)) {
		vel.x = abs(vel.x) + lp->getVel()->x;
		vel.y = vel.y + lp->getVel()->y;
    }
    if (collision(rp)) {
		vel.x = -abs(vel.x) + rp->getVel()->x;
		vel.y =  vel.y + rp->getVel()->y;
    }

    // Wall collision
    if ((pos->y < 0) || (pos->y + Ball::HEIGHT > screenHeight)) {
        pos->y -= vel.y;
        vel.y = -vel.y;
        collider.y = pos->y;
    }
}

bool Ball::collision(Paddle* paddle)
{
    if (paddle == NULL)
        return false;

    SDL_Rect* pc = paddle->getCollider();

    int lb = collider.x, rb = collider.x + collider.w, tb = collider.y,
        bb = collider.y + collider.h;

    int lp = pc->x, rp = pc->x + pc->w, tp = pc->y, bp = pc->y + pc->h;

    return !(bb <= tp || tb >= bp || rb <= lp || lb >= rp);
}

void drawCircle(SDL_Renderer* pRenderer, SDL_Point* center, uint8_t radius)
{
    SDL_SetRenderDrawColor(pRenderer, 0x00, 0xFF, 0xFF, 0xFF);
    for (int w = 0; w < radius * 2; w++)
        for (int h = 0; h < radius * 2; h++) {
            int dx = radius - w;
            int dy = radius - h;
            if ((dx * dx + dy * dy) <= (radius * radius)) {
                SDL_RenderDrawPoint(pRenderer, center->x + dx, center->y + dy);
            }
        }
}

void Ball::render(SDL_Renderer* pRenderer)
{
    uint8_t radius = Ball::WIDTH / 2;
    drawCircle(
        pRenderer, new SDL_Point{ pos->x + radius, pos->y + radius }, radius);
}
