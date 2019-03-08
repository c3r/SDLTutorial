#include "Paddle.h"
#include <iostream>
#include <map>
#include "Ball.h"
#include "TextureManager.h"

Paddle::Paddle(std::string textureId, SDL_Point* pStartPos, SDL_Rect* tableRect,
	SDL_Keycode upKey, SDL_Keycode downKey,
        SDL_Keycode leftKey, SDL_Keycode rightKey, SDL_Rect* clipRect,
        short int serveDirection) {
        textureId = textureId;
        m_upKey = upKey;
        m_downKey = downKey;
        m_leftKey = leftKey;
        m_rightKey = rightKey;
        m_serveDirection = serveDirection;

        m_points = 0;

        m_pos = pStartPos;
        m_vel = { 0, 0 };

	m_tableRect = tableRect;

        m_keymap = { {downKey, 5}, {upKey, -5} };

        m_clip = clipRect;
        m_collider = { m_pos->x, m_pos->y, Paddle::WIDTH, Paddle::HEIGHT };
}

Paddle::Paddle() {
        m_pos = new SDL_Point{ 0, 0 };
        m_vel = { 0, 0 };
}

short int Paddle::getServeDirection() { return m_serveDirection; }

void Paddle::handleEvent(SDL_Event& e) {
        //int v = Paddle::VELOCITY;
        int v = 5; 
        if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
                if (e.key.keysym.sym == m_upKey) {
                        m_vel.y -= v;
                        return;
                }
                if (e.key.keysym.sym == m_downKey) {
                        m_vel.y += v;
                        return;
                }
                if (e.key.keysym.sym == m_leftKey) {
                        m_vel.x -= v;
                        return;
                }
                if (e.key.keysym.sym == m_rightKey) {
                        m_vel.x += v;
                        return;
                }
        }

        if (e.type == SDL_KEYUP && e.key.repeat == 0) {
                if (e.key.keysym.sym == m_upKey) {
                        m_vel.y += v;
                        return;
                }
                if (e.key.keysym.sym == m_downKey) {
                        m_vel.y -= v;
                        return;
                }
                if (e.key.keysym.sym == m_leftKey) {
                        m_vel.x += v;
                        return;
                }
                if (e.key.keysym.sym == m_rightKey) {
                        m_vel.x -= v;
                        return;
                }
        }

        if (e.type == SDL_KEYUP && e.key.repeat == 0) {
                if (e.key.keysym.sym == SDLK_SPACE && m_stickingBall != nullptr) {
                        m_stickingBall->unstick(this);
                        m_stickingBall = nullptr;
                }
        }
}

SDL_Point* Paddle::getMiddlePoint() {
        return new SDL_Point{ m_pos->x + 30 / 2,
                             m_pos->y + 30 / 2 };
}

void Paddle::move() {
        m_pos->x += m_vel.x;
        m_collider.x = m_pos->x;

        int bw = Ball::WIDTH;
        int pw = Paddle::WIDTH;
        int mid = (m_tableRect->x + m_tableRect->w) / 2;

        // TODO: Create midblock collider and check for collision here.
        bool inMiddle = m_pos->x < (mid - pw - bw) || m_pos->x > (mid + bw);

        if ((m_pos->x < m_tableRect->x) || !inMiddle || (m_pos->x + pw > m_tableRect->x + m_tableRect->w)) {
                m_pos->x -= m_vel.x;
                m_collider.x = m_pos->x;
        }

	int ph = Paddle::HEIGHT;
        m_pos->y += m_vel.y;
        m_collider.y = m_pos->y;
	if ((m_pos->y <= m_tableRect->y) || (m_pos->y + ph > m_tableRect->y + m_tableRect->h)) {
                m_pos->y -= m_vel.y;
                m_collider.y = m_pos->y;
        }
}

void Paddle::addPoint() { m_points++; }

SDL_Point* Paddle::getPosition() { return m_pos; }

Velocity* Paddle::getVel() { return &m_vel; }

std::string Paddle::getPoints() {
        std::string out_string;
        std::stringstream ss;
        ss << m_points;
        return ss.str();
}

void Paddle::stick(Ball* ball) { m_stickingBall = ball; }

bool Paddle::isBallSticking(Ball* ball) { return ball == m_stickingBall; }

void Paddle::render(SDL_Renderer* pRenderer) {
        
	int a = 4;
	SDL_Rect r1 = { m_collider.x, m_collider.y, m_collider.w - a, m_collider.h };
	SDL_Rect r2 = { m_collider.x + a, m_collider.y, m_collider.w - 2*a, m_collider.h };
	SDL_Rect r3 = { m_collider.x + m_collider.w - a, m_collider.y, a, m_collider.h };

	SDL_SetRenderDrawColor(pRenderer, 0xFF, 0x00, 0x00, 0xAA);
        SDL_RenderFillRect(pRenderer, &r1);
	SDL_SetRenderDrawColor(pRenderer, 0xCC, 0xA7, 0x53, 0xAA);
	SDL_RenderFillRect(pRenderer, &r2);
	SDL_SetRenderDrawColor(pRenderer, 0xFF, 0x00, 0x00, 0xAA);
	SDL_RenderFillRect(pRenderer, &r3);
}

SDL_Rect* Paddle::getCollider() { return &m_collider; }
