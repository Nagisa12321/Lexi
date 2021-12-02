// author: Jacky Boen

#include "SDL_timer.h"
#include <SDL.h>

static const char *window_title = "SDL2 Events";
static const int window_width = 800, window_height = 600;
static SDL_Joystick *joysticks[16];

int main() {
	SDL_Window *window;
	SDL_bool running = SDL_TRUE;

	SDL_Init(SDL_INIT_EVERYTHING);

	window = SDL_CreateWindow(window_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window_width, window_height, SDL_WINDOW_SHOWN);
	if (!window) {
		fprintf(stderr, "%s\n", SDL_GetError());
		return -1;
	}


	while (running) {
		SDL_Event event;

		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:

				running = SDL_FALSE;
				break;
			case SDL_MOUSEMOTION:
				fprintf(stdout, "[%d ms] MouseMotion\ttype:%d\twhich:\tx:%d\ty:%d\txrel:%d\tyrel:%d\n",
					event.motion.timestamp, event.motion.type, event.motion.which, event.motion.x, event.motion.y, event.motion.xrel, event.motion.yrel);
				break;
			case SDL_MOUSEBUTTONDOWN:
			case SDL_MOUSEBUTTONUP:
				fprintf(stdout, "[%d ms] MouseButton\ttype:%d\tid:%d\tx:%d\ty:%d\tbutton:%d\tstate:%d\n",
					event.button.timestamp, event.button.type, event.button.which, event.button.x, event.button.y, event.button.button, event.button.state);
				break;
			case SDL_MOUSEWHEEL:
				fprintf(stdout, "[%d ms] MouseWheel\ttype:%d\tid:%d\tx:%d\ty:%d\n",
					event.wheel.timestamp, event.wheel.type, event.wheel.which, event.wheel.x, event.wheel.y);
				break;
			case SDL_KEYDOWN:
			case SDL_KEYUP:
				fprintf(stdout, "[%d ms] Keyboard\ttype:%d\twindowID:%d\tsym:%c\tmodifiers:%d\tstate:%d\trepeat:%d\n",
					event.key.timestamp, event.key.type, event.key.windowID, event.key.keysym.sym, event.key.keysym.mod, event.key.state, event.key.repeat);
				break;
			default:
				fprintf(stdout, "Some event\n");
				break;
			}
		}

        SDL_Delay(1000 / 60);
	}

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}