#include "Ball.h"
#include "Paddle.h"
#include <cstdlib>

Ball::Ball(std::string textureId,
    SDL_Point* startingPos,
    uint16_t screenW,
    uint16_t screenH,
    SDL_Rect* clipRect)
{
    textureId = textureId;
    m_pos = startingPos;
    m_vel = { Ball::VEL, 2 };
    screenHeight = screenH;
    screenWidth = screenW;
    m_clip = clipRect;
    m_collider = { m_pos->x, m_pos->y, Ball::WIDTH, Ball::HEIGHT };
    //m_stickPaddle = NULL;
}

Ball::~Ball() {}

void Ball::handleEvent(SDL_Event& e)
{
}

void Ball::checkForScore(Paddle* lPaddle, Paddle* rPaddle)
{
    // Right scores
    if (m_pos->x + Ball::WIDTH < 0) {
        rPaddle->addPoint();
        m_pos = lPaddle->getBallServePositionLeft();
        stickToPaddle(lPaddle);
        m_vel = { 0, 0 };
    }

    // Left scores
    if (m_pos->x - Ball::WIDTH > screenWidth) {
        lPaddle->addPoint();
        m_pos = rPaddle->getBallServePositionRight();
        stickToPaddle(rPaddle);
        m_vel = { 0, 0 };
    }
}

void Ball::stickToPaddle(Paddle* paddle)
{
    m_stickPaddle = paddle;
    paddle->stickToPaddle(this);
}

void Ball::move(Paddle* lp, Paddle* rp)
{
	 // Check for sticking paddle
    if (m_stickPaddle == rp) {
        m_pos = m_stickPaddle->getBallServePositionRight();
        return;
    }

    if (m_stickPaddle == lp) {
        m_pos = m_stickPaddle->getBallServePositionLeft();
        return;
    }

    // Accelerate
    if (m_vel.x > 0.05) {
        m_vel = { m_vel.x - 0.105, m_vel.y };
    }
    if (m_vel.x < -0.05) {
        m_vel = { m_vel.x + 0.11, m_vel.y };
    }

    // Move
    m_collider.x = m_pos->x += m_vel.x; // Move in x axis
    m_collider.y = m_pos->y += m_vel.y; // Move in Y axis

    // Check for score
    checkForScore(lp, rp);

    // Check for collisions
    if (checkCollisionWithPaddle(lp)) {
        m_vel.x = Ball::VEL;
    }
    if (checkCollisionWithPaddle(rp)) {
        m_vel.x = -Ball::VEL;
    }

    // Wall collision
    if ((m_pos->y < 0) || (m_pos->y + Ball::HEIGHT > screenHeight)) {
        m_pos->y -= m_vel.y;
        m_vel.y = -m_vel.y;
        m_collider.y = m_pos->y;
    }
}

bool Ball::checkCollisionWithPaddle(Paddle* paddle)
{
    if (paddle == NULL)
        return false;

    SDL_Rect* pc = paddle->getCollider();

    int lb = m_collider.x, rb = m_collider.x + m_collider.w, tb = m_collider.y,
        bb = m_collider.y + m_collider.h;

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
        pRenderer, new SDL_Point{ m_pos->x + radius, m_pos->y + radius }, radius);
}

//void Ball::stickToPaddle(Paddle* pPaddle)
//{
//    m_stickPaddle = pPaddle;
//    pPaddle->stickToPaddle(this);
//}
