#include "Ball.h"
#include "Paddle.h"
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
    SDL_Rect* clipRect,
    short int serveDirection)
{
    textureId = textureId;
    m_upKey = upKey;
    m_downKey = downKey;
    m_leftKey = leftKey;
    m_rightKey = rightKey;
    m_serveDirection = serveDirection;

    m_points = 0;

    m_pos = pStartPos;
    m_vel = { 0, 0 };

    scrH = screenH; // TODO: Externalize!
    scrW = screenW;

    m_keymap = {{ downKey, Paddle::VELOCITY  }, 
               {  upKey,  -Paddle::VELOCITY }};
               
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

short int Paddle::getServeDirection() 
{
    return m_serveDirection;
}

void Paddle::handleEvent(SDL_Event& e)
{
	int v = Paddle::VELOCITY;
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) { 
        if (e.key.keysym.sym == m_upKey)	{ m_vel.y -= v; return; }
		if (e.key.keysym.sym == m_downKey)	{ m_vel.y += v; return; }
		if (e.key.keysym.sym == m_leftKey)	{ m_vel.x -= v; return; }
		if (e.key.keysym.sym == m_rightKey) { m_vel.x += v; return; }
    }

    if (e.type == SDL_KEYUP && e.key.repeat == 0) {
        if (e.key.keysym.sym == m_upKey)	{ m_vel.y += v; return; }
        if (e.key.keysym.sym == m_downKey)	{ m_vel.y -= v; return; }
        if (e.key.keysym.sym == m_leftKey)	{ m_vel.x += v; return; }
        if (e.key.keysym.sym == m_rightKey)	{ m_vel.x -= v; return; }
    }

    if (e.type == SDL_KEYUP && e.key.repeat == 0) {
        if (e.key.keysym.sym == SDLK_SPACE && m_stickingBall != nullptr) 
        {
            m_stickingBall->unstick(this);
            m_stickingBall = nullptr; 
        }
    }
}

void Paddle::move()
{
    m_pos->x += m_vel.x;
    m_collider.x = m_pos->x;

    int bw = Ball::WIDTH;
    int pw = Paddle::WIDTH;
    int ph = Paddle::HEIGHT;
    int middle = scrW/2;

    // TODO: Create midblock collider and check for collision here.
    bool midBlock = m_pos->x < middle - pw - bw 
                 || m_pos->x > middle + bw;

    if ((m_pos->x < 0) || !midBlock || (m_pos->x + pw > scrW)) {
        m_pos->x -= m_vel.x;
        m_collider.x = m_pos->x;
    }

    m_pos->y += m_vel.y; 
    m_collider.y = m_pos->y;
    if ((m_pos->y < 0) || (m_pos->y + ph > scrH)) {
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

SDL_Point* Paddle::getVel()
{
	return &m_vel;
}

std::string Paddle::getPoints()
{
    std::string out_string;
    std::stringstream ss;
    ss << m_points;
    return ss.str();
}

void Paddle::stick(Ball* ball)
{
    m_stickingBall = ball;
}

bool Paddle::isBallSticking(Ball* ball) 
{
    return ball == m_stickingBall;
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
