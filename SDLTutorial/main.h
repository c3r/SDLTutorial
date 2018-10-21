#pragma once

#include <vector>
#include "Ball.h"
#include "LTexture.h"
#include "Paddle.h"

const int SW = 640;
const int SH = 480;

const int TABLE_HEIGHT = 380;
const int TABLE_WIDTH = 630;
const int TABLE_MARGIN_LEFT = 5;
const int TABLE_MARGIN_TOP = 70;

const int SERVE_DIRECTION_LEFT = -1;
const int SERVE_DIRECTION_RIGHT = 1;

bool init();
void close();
std::vector<SDL_Event>& GetFrameEvents();
bool loadTTFMedia();

SDL_Window* gWindow = NULL;
SDL_Renderer* g_renderer = NULL;

TTF_Font* gFont = NULL;
LTexture* g_rpScore = NULL;
LTexture* g_lpScore = NULL;

bool gQuit = false;
