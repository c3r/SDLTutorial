#pragma once
#include "Geometry.h"
#include "TextureManager.h"
#include <string>

class Paddle;

class Ball {
public:
    static const int WIDTH = 20;
    static const int HEIGHT = 20;
    static const int VEL = 4;

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

    SDL_Point* pos;
    Velocity vel;
    SDL_Rect* clip;
    SDL_Rect collider;
    std::string textureId;

    // Externalize!
    int screenWidth, screenHeight;
    void handleScore(Paddle* lp, Paddle* rp);
};
