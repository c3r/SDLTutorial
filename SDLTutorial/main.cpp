#include "main.h"

bool init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    // Set texture filtering to linear
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
        printf("Warning: Linear texture filtering not enabled!");
    }

    gWindow = SDL_CreateWindow("SDL Tutorial",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SW,
        SH,
        SDL_WINDOW_SHOWN);

    if (gWindow == NULL) {
        printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    // Create renderer for window
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

    if (gRenderer == NULL) {
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        return false;
    }

	gLScore = new LTexture(gRenderer);
	gRScore = new LTexture(gRenderer);

    // Initialize renderer color
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

    // Initialize PNG loading
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        printf("SDL_image could not initialize! SDL_image Error: %s\n",
            IMG_GetError());
        return false;
    }

    //Initialize SDL_ttf
    if (TTF_Init() == -1) {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        return false;
    }

    return true;
}

bool loadTTFMedia()
{
    gFont = TTF_OpenFont("img/7segment.ttf", 72);

    if (gFont == NULL) {
        printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
        return false;
    }

    SDL_Color textColor = { 0xFF, 0xFF, 0xFF };
    
    return true;
}

void close()
{
    TTF_CloseFont(gFont);
    gFont = NULL;

    // Destroy window
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;

    // Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

void render(Paddle* pLeftPaddle, Paddle* pRightPaddle, Ball* pBall)
{
    SDL_SetRenderDrawColor(gRenderer, 0x10, 0x30, 0x60, 0xFF);
    SDL_RenderClear(gRenderer);

    TheTextureManager::Instance()->draw("_bg_", 0, 0);
    
	SDL_Color white = { 255, 255, 255, 255 };
    int centerMargin = 20;

    gLScore->loadFromRenderedText(pLeftPaddle->getPoints(), white, gFont);
    gRScore->loadFromRenderedText(pRightPaddle->getPoints(), white, gFont);

	gLScore->render(SW / 2 - centerMargin - gLScore->getWidth(), centerMargin, gRenderer);
    gRScore->render(SW / 2 + centerMargin, centerMargin, gRenderer);

    pLeftPaddle->render(gRenderer);
    pRightPaddle->render(gRenderer);
    pBall->render(gRenderer);

    SDL_RenderPresent(gRenderer);
}

std::vector<SDL_Event>& GetFrameEvents()
{
    static std::vector<SDL_Event> frame_events;
    return frame_events;
}

void handleEvents(Paddle* paddle1, Paddle* paddle2, Ball* ball)
{
    SDL_Event _event;
    while (SDL_PollEvent(&_event) != 0) {
        GetFrameEvents().push_back(_event);
    }

    for (auto& event : GetFrameEvents()) {
        if (event.type == SDL_QUIT)
            gQuit = true;

        paddle1->handleEvent(event);
        paddle2->handleEvent(event);
        ball->handleEvent(event);
    }
}

void updateState(Paddle* paddle1, Paddle* paddle2, Ball* ball, uint32_t cTime)
{
    paddle1->move();
    paddle2->move();
    ball->move(paddle1, paddle2);
}

int main(int argc, char* args[])
{
    if (!init()) {
        printf("Failed to initialize!\n");
        return 0;
    }

    if (!loadTTFMedia()) {
        printf("Failed to load font media!\n");
        return 0;
    }

    // Init game objects
    //TheTextureManager::Instance()->load("img/sprites.png", "_sprites_", gRenderer);
    TheTextureManager::Instance()->load("img/bg.png", "_bg_", gRenderer);

    // Paddles
    Paddle* paddle_1 = new Paddle("p1",
        new SDL_Point{ Paddle::WIDTH, SH / 2 - Paddle::HEIGHT / 2 },
        SW,
        SH,
        SDLK_w,
        SDLK_s,
		SDLK_a,
		SDLK_d,
        new SDL_Rect{ 0, 0, Paddle::WIDTH, Paddle::HEIGHT });

    Paddle* paddle_2 = new Paddle(
        "p2",
        new SDL_Point{ SW - 2 * Paddle::WIDTH, SH / 2 - Paddle::HEIGHT / 2 },
        SW,
        SH,
        SDLK_UP,
        SDLK_DOWN,
        SDLK_LEFT,
        SDLK_RIGHT,
        new SDL_Rect{ Paddle::WIDTH, 0, Paddle::WIDTH, Paddle::HEIGHT });

    // Ball
    Ball* ball = new Ball(
        "_sprites_",
        new SDL_Point{ SW / 2 - Ball::WIDTH / 2, SH / 2 - Ball::HEIGHT / 2 },
        SW,
        SH,
        new SDL_Rect{ 100, 0, Ball::WIDTH, Ball::HEIGHT });

    // Frame rate governing
    int32_t ticksPerSecond = 60;
    int32_t tickInterval = 1000 / ticksPerSecond;
    uint32_t lastUpdateTime = 0;
    double dt = 0;

    while (!gQuit) {
        uint32_t currentTime = SDL_GetTicks();
        dt = (currentTime - lastUpdateTime);
        int32_t timeToSleep = tickInterval - dt;

        if (timeToSleep > 0)
            SDL_Delay(timeToSleep);

        handleEvents(paddle_1, paddle_2, ball);
        updateState(paddle_1, paddle_2, ball, currentTime);
        render(paddle_1, paddle_2, ball);

        lastUpdateTime = currentTime;

        GetFrameEvents().clear();
    }

    close();
    return 0;
}
