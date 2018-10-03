#ifndef __MAIN__
#define __MAIN__

#ifndef __INCSDL__
#include <SDL.h>
#define __INCSDL__
#endif

//#include <string>
#include <vector>

//#include <SDL_image.h>
//#include <SDL_ttf.h>
//#include <stdio.h>
//#include <cmath>
//#include <sstream>
//#include <iostream>
//#include <iomanip>
//#include <map>

const int SW = 640;
const int SH = 480;

bool init();

void close();
std::vector<SDL_Event>& GetFrameEvents();

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

bool gQuit = false;

#endif
