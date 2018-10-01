#include "main.h"
#include "Paddle.h"

bool init()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		return false;
	}

	//Set texture filtering to linear
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
		printf("Warning: Linear texture filtering not enabled!");
	}

	gWindow = SDL_CreateWindow("SDL Tutorial",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN);

	if (gWindow == NULL) {
		printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
		return false;
	}

	//Create renderer for window
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
	if (gRenderer == NULL) {
		printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
		return false;
	}

	//Initialize renderer color
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

	//Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags)) {
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		return false;
	}

	return true;
}


void close()
{
	//Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}


void render(Paddle *dot)
{
	SDL_SetRenderDrawColor(gRenderer, 0x10, 0x30, 0x60, 0xFF);
	SDL_RenderClear(gRenderer);
	dot->render();
	SDL_RenderPresent(gRenderer);
}

std::vector<SDL_Event>& GetFrameEvents()
{
	static std::vector<SDL_Event> frame_events;
	return frame_events;
}

void handleEvents(Paddle *dot)
{
	SDL_Event _event;
	while (SDL_PollEvent(&_event) != 0) {
		GetFrameEvents().push_back(_event);
	}

	for (auto &event : GetFrameEvents()) {
		if (event.type == SDL_QUIT)
			gQuit = true;

		dot->handleEvent(event);
	}
}

void updateState(Paddle *dot) 
{
	dot->move();
}

int main(int argc, char* args[]) 
{
	if (!init()) {
		printf("Failed to initialize!\n");
		return 0;
	}

	LTexture *dotTexture = new LTexture(gRenderer);
	dotTexture->loadFromFile("img/dot.bmp");
	Paddle *dot = new Paddle(SCREEN_WIDTH, SCREEN_HEIGHT, dotTexture);

	int32_t ticksPerSecond = 60;
	int32_t tickInterval = 1000 / ticksPerSecond; // frequency in Hz to period in ms
	uint32_t lastUpdateTime = 0;
	double dt = 0;

	while (!gQuit) 
	{
		uint32_t currentTime = SDL_GetTicks();
		dt = (currentTime - lastUpdateTime);
		int32_t timeToSleep = tickInterval - dt;

		if (timeToSleep > 0)
			SDL_Delay(timeToSleep);

		handleEvents(dot);
		updateState(dot);
		render(dot);

		lastUpdateTime = currentTime;

		GetFrameEvents().clear();
	}

	dotTexture->free(); // TODO: przeniesc gdzies 

	close();
	system("pause");
	return 0;
}

