#include "SDL2/SDL.h"
#include <iostream>

using namespace std;

int main() {
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *window = SDL_CreateWindow("cycle. ", 
                                          100,
                                          100,
                                          600,
                                          600,
                                          SDL_WINDOW_SHOWN);

    bool running = true;
    SDL_Renderer *screen = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    while (1) {
        SDL_Event event;
        int x, y;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                cout << "SDL_QUIT" << endl;
                running = false;
                break;
            }
        }
        if (!running)
            break;
        
        SDL_Delay(100);
    }

    SDL_DestroyRenderer(screen);
    SDL_DestroyWindow(window);
    SDL_Quit();
}