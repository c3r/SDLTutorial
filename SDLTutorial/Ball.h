#pragma once
#include "Geometry.h"
#include "TextureManager.h"
#include <string>

class Paddle;

class Ball {
public:
    static const int WIDTH = 20;
    static const int HEIGHT = 20;
    static const int VEL = 5;

    Ball(std::string textureId,
        SDL_Point* startingPos,
        uint16_t screenW,
        uint16_t screenH,
        SDL_Rect* clipRect);

    ~Ball();

    void handleEvent(SDL_Event& e);
    void move(Paddle* paddle1, Paddle* paddle2);
    bool collision(Paddle* paddle);
    void render(SDL_Renderer* renderer);
    void stickTo(Paddle* paddle);
    void unstick(Paddle* paddle); // TODO: serve() ?

private:

    SDL_Point* m_pos;
    Velocity m_vel;
    SDL_Rect* m_clip;
    SDL_Rect m_collider;
    std::string m_textureId;

    // Externalize!
    int screenWidth, screenHeight;
    void handleScore(Paddle* leftPaddle, Paddle* rightPaddle);
};
