#pragma once 

#include <vector>
#include "LTexture.h"
#include "Ball.h"
#include "Paddle.h"

const int SW = 640;
const int SH = 480;
const int SERVE_DIRECTION_LEFT = -1;
const int SERVE_DIRECTION_RIGHT = 1;

bool init();
void close();
std::vector<SDL_Event>&
GetFrameEvents();
bool loadTTFMedia();

SDL_Window* gWindow = NULL;
SDL_Renderer* g_renderer = NULL;

TTF_Font* gFont = NULL;
LTexture* g_rpScore = NULL;
LTexture* g_lpScore = NULL;

bool gQuit = false;
