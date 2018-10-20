#pragma once
#include "LTexture.h"
#include "ScreenText.h"
#include "Ball.h"
#include <map>
#include <sstream>

class Paddle {
public:
    static const int WIDTH = 10;
    static const int HEIGHT = 50;
	static const int VELOCITY = 3;

    Paddle(std::string textureId,
        SDL_Point* startPos,
        uint16_t screenW,
        uint16_t screenH,
        SDL_Keycode upKey,
        SDL_Keycode downKey,
        SDL_Keycode leftKey,
        SDL_Keycode rightKey,
        SDL_Rect* clipRect,
        short int serveDirection);

    Paddle();

    void handleEvent(SDL_Event& e);
    void move();
    void render(SDL_Renderer* renderer);
    SDL_Point* getPosition();
    SDL_Rect* getCollider();
    std::string getPoints();
    void addPoint();
    SDL_Point* getBallServePositionLeft();
    SDL_Point* getBallServePositionRight();
    void stick(Ball* ball);
    bool isBallSticking(Ball *ball);
    short int getServeDirection();

private:
    SDL_Keycode m_upKey, m_downKey, m_leftKey, m_rightKey;
    std::string m_textureId;
    SDL_Point* m_pos;
    SDL_Point m_vel;
    std::map<SDL_Keycode, int> m_keymap;
    SDL_Rect* m_clip;
    SDL_Rect m_collider;
    short int m_points;
    Ball* m_stickingBall;
    short int m_serveDirection;

    // TODO: externalize!
    int scrW, scrH;
};
