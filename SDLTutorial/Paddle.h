#pragma once
#include <map>
#include <sstream>
#include "Ball.h"
#include "LTexture.h"
#include "ScreenText.h"

class Paddle {
public:
        static const int WIDTH = 20;
        static const int HEIGHT = 80;
        static const int VELOCITY = 3;

        Paddle(std::string textureId, SDL_Point* startPos, SDL_Rect* tableRect, 
		SDL_Keycode upKey, SDL_Keycode downKey,
                SDL_Keycode leftKey, SDL_Keycode rightKey, SDL_Rect* clipRect,
                short int serveDirection);

        Paddle();

        void handleEvent(SDL_Event& e);
        SDL_Point* getMiddlePoint();
        void move();
        void render(SDL_Renderer* renderer);
        SDL_Point* getPosition();
        SDL_Rect* getCollider();
        std::string getPoints();
        void addPoint();
        SDL_Point* getBallServePositionLeft();
        SDL_Point* getBallServePositionRight();
        void stick(Ball* ball);
        bool isBallSticking(Ball* ball);
        short int getServeDirection();
        Velocity* getVel();

private:
        SDL_Keycode m_upKey, m_downKey, m_leftKey, m_rightKey;
        std::string m_textureId;
        SDL_Point* m_pos;
        Velocity m_vel;
        std::map<SDL_Keycode, int> m_keymap;
        SDL_Rect* m_clip;
	SDL_Rect* m_tableRect;
        SDL_Rect m_collider;
        short int m_points;
        Ball* m_stickingBall;
        short int m_serveDirection;
};
