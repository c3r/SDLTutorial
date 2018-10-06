#include "Paddle.h"
#include "Ball.h"
#include "TextureManager.h"
#include <iostream>
#include <map>

Paddle::Paddle(std::string textureId,
    SDL_Point* pStartPos,
    uint16_t screenW,
    uint16_t screenH,
    SDL_Keycode upKey,
    SDL_Keycode downKey,
	SDL_Keycode leftKey,
	SDL_Keycode rightKey,
    SDL_Rect* clipRect)
{
    textureId = textureId;
    m_upKey = upKey;
    m_downKey = downKey;
    m_leftKey = leftKey;
    m_rightKey = rightKey;

    m_points = 0;

    m_pos = pStartPos;
    m_vel = { 0, 0 };

    scrH = screenH; // TODO: Externalize!
    scrW = screenW;

    m_keymap = { { downKey, static_cast<int>(VELOCITY) }, { upKey, -1*static_cast<int>(VELOCITY) } };
    m_clip = clipRect;
    m_collider = { m_pos->x, m_pos->y, Paddle::WIDTH, Paddle::HEIGHT };
}

Paddle::Paddle()
{
    m_pos = new SDL_Point{ 0, 0 };
    m_vel = { 0, 0 };
    scrH = 0;
    scrW = 0;
}

void Paddle::handleEvent(SDL_Event& e)
{
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        if (e.key.keysym.sym == m_upKey)	{ m_vel.y -= 5; return; }
		if (e.key.keysym.sym == m_downKey)	{ m_vel.y += 5; return; }
		if (e.key.keysym.sym == m_leftKey)	{ m_vel.x -= 5; return; }
		if (e.key.keysym.sym == m_rightKey) { m_vel.x += 5; return; }
    }

    if (e.type == SDL_KEYUP && e.key.repeat == 0) {
        if (e.key.keysym.sym == m_upKey)	{ m_vel.y += 5; return; }
        if (e.key.keysym.sym == m_downKey)	{ m_vel.y -= 5; return; }
        if (e.key.keysym.sym == m_leftKey)	{ m_vel.x += 5; return; }
        if (e.key.keysym.sym == m_rightKey)	{ m_vel.x -= 5; return; }
    }
}

void Paddle::move()
{
    m_pos->x += m_vel.x;
    m_collider.x = m_pos->x;
    if ((m_pos->x < 0) || (m_pos->x + Paddle::WIDTH > scrW)) {
        m_pos->x -= m_vel.x;
        m_collider.x = m_pos->x;
    }

    m_pos->y += m_vel.y;
    m_collider.y = m_pos->y;
    if ((m_pos->y < 0) || (m_pos->y + Paddle::HEIGHT > scrH)) {
        m_pos->y -= m_vel.y;
        m_collider.y = m_pos->y;
    }
}

void Paddle::addPoint()
{
    m_points++;
}

SDL_Point* Paddle::getPosition()
{
    return m_pos;
}

std::string Paddle::getPoints()
{
    std::string out_string;
    std::stringstream ss;
    ss << m_points;
    return ss.str();
}

SDL_Point* Paddle::getBallServePositionLeft()
{
    return new SDL_Point{ m_pos->x + Paddle::WIDTH,
        m_pos->y + Paddle::HEIGHT / 2 };
}

SDL_Point* Paddle::getBallServePositionRight()
{
    return new SDL_Point{ m_pos->x - Ball::WIDTH, m_pos->y + Paddle::HEIGHT / 2 };
}

void Paddle::stickToPaddle(Ball* ball)
{
    m_stickingBall = ball;
}

void Paddle::render(SDL_Renderer* pRenderer)
{
    SDL_SetRenderDrawColor(pRenderer, 0xFF, 0x00, 0x00, 0xFF);
    SDL_RenderFillRect(pRenderer, &m_collider);
}

SDL_Rect* Paddle::getCollider()
{
    return &m_collider;
}
