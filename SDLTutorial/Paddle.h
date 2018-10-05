#pragma once
#include "LTexture.h"
#include "ScreenText.h"
#include "Ball.h"
#include <map>
#include <sstream>

class Paddle {
public:
    static const int WIDTH = 15;
    static const int HEIGHT = 100;
    static const int VEL = 5;

    Paddle(std::string textureId,
        SDL_Point* startPos,
        uint16_t screenW,
        uint16_t screenH,
        SDL_Keycode upKey,
        SDL_Keycode downKey,
        SDL_Keycode leftKey,
        SDL_Keycode rightKey,
        SDL_Rect* clipRect);

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
    void stickToPaddle(Ball* ball);

private:
    SDL_Keycode m_upKey, m_downKey, m_leftKey, m_rightKey;
    std::string m_textureId;
    SDL_Point* m_pos;
    SDL_Point m_vel;
    std::map<SDL_Keycode, Sint8> m_keymap;
    SDL_Rect* m_clip;
    SDL_Rect m_collider;
    int m_points;
    Ball* m_stickingBall;

    // TODO: externalize!
    int scrW, scrH;
};