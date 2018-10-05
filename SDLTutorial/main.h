#pragma once 

#include <vector>
#include "LTexture.h"
#include "Ball.h"
#include "Paddle.h"

const int SW = 640;
const int SH = 480;

bool init();
void close();
std::vector<SDL_Event>&
GetFrameEvents();
bool loadTTFMedia();

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

TTF_Font* gFont = NULL;
LTexture* gRScore = NULL;
LTexture* gLScore = NULL;

bool gQuit = false;
