#pragma once
#include <string>
#include "Geometry.h"
#include "TextureManager.h"

class Paddle;

class Ball {
public:
        static const int WIDTH = 20;
        static const int HEIGHT = 20;
        static const int VEL = 4;

        Ball(SDL_Point* startingPos, SDL_Rect* tableRect);

        ~Ball();

        void handleEvent(SDL_Event& e);
        void move(Paddle* paddle1, Paddle* paddle2);
        bool stickToPaddle();
        void collide(Paddle* cp);
        void setMiddlePoint(SDL_Point* point);
        bool collision(Paddle* paddle);
        void render(SDL_Renderer* renderer);
        void stickTo(Paddle* paddle);
        void unstick(Paddle* paddle);  // TODO: serve() ?

private:
        SDL_Point* pos;
        Velocity vel;
        SDL_Rect collider;
        Paddle* stickingPaddle;
	SDL_Rect* tableRect;
        
	bool checkForScore(Paddle* lp, Paddle* rp);
        void handleScore(Paddle* scoring, Paddle* serving);
};
