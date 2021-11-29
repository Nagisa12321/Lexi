#include "SDL2/SDL.h"
#include "Window.h"

// definitely lost: 7,176 bytes in 4 blocks
int main() {
    SDL_Init(SDL_INIT_EVERYTHING);
    for (int i = 0; i < 100; ++i) {
        Window *window = new Window({100, 100, 300, 300}, "test leak");
        delete window;
    }
    SDL_Delay(5000);
    SDL_Quit();
}