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
}

Ball::~Ball() {}

void Ball::handleEvent(SDL_Event& e)
{
}

void Ball::handleScore(Paddle* lp, Paddle* rp)
{
    // Right scores
    if (m_pos->x + Ball::WIDTH < 0) {
        rp->addPoint();
        lp->stick(this);

        m_pos = new SDL_Point { 
            lp->getPosition()->x + Paddle::WIDTH,
            lp->getPosition()->y + Paddle::HEIGHT / 2 };

        m_vel = { 0, 0 };
        return;
    }
    // Left scores
    if (m_pos->x - Ball::WIDTH > screenWidth) {
        lp->addPoint();
        rp->stick(this);

        m_pos = new SDL_Point { 
            rp->getPosition()->x - Paddle::WIDTH,
            rp->getPosition()->y + Paddle::HEIGHT / 2 };
        
        m_vel = { 0, 0 };
        return;
    }
}

void Ball::unstick(Paddle* p)
{
    m_vel.x = p->getServeDirection() * Ball::VEL;
    m_vel.y = SDL_GetTicks() % 2 == 0 ? -2 : 2; // TODO: zrobic to jakos lepiej, lol
}

void Ball::move(Paddle* lp, Paddle* rp)
{
    if (lp->isBallSticking(this)) {
        m_pos = new SDL_Point { 
            lp->getPosition()->x + Paddle::WIDTH,
            lp->getPosition()->y + Paddle::HEIGHT / 2 };
        return;
    }

    if (rp->isBallSticking(this)) {
        m_pos = new SDL_Point { 
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
    m_collider.x = m_pos->x += m_vel.x; // Move in x axis
    m_collider.y = m_pos->y += m_vel.y; // Move in Y axis

    // Check for score
    handleScore(lp, rp);

    // Check for collisions
    if (collision(lp)) {
        m_vel.x = Ball::VEL;
    }
    if (collision(rp)) {
        m_vel.x = -Ball::VEL;
    }

    // Wall collision
    if ((m_pos->y < 0) || (m_pos->y + Ball::HEIGHT > screenHeight)) {
        m_pos->y -= m_vel.y;
        m_vel.y = -m_vel.y;
        m_collider.y = m_pos->y;
    }
}

bool Ball::collision(Paddle* paddle)
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
