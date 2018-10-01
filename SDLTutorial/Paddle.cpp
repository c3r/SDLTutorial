#include "Paddle.h"
#include <map>

void Paddle::handleEvent(SDL_Event& e)
{
	static std::map<SDL_Keycode, Sint8> keymap{ {SDLK_UP, 5}, {SDLK_DOWN, -5} };

	if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
		vel += keymap[e.key.keysym.sym];
	}

	if (e.type == SDL_KEYUP && e.key.repeat == 0) {
		vel -= keymap[e.key.keysym.sym];
	}
}

