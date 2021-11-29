#include "SDL2/SDL.h"
#include "Window.h"

// definitely lost: 7,176 bytes in 4 blocks
int main() {
    SDL_Init(SDL_INIT_EVERYTHING);
    Window *win = new Window({10, 10, 600, 600}, "the window");
    win->draw_rect({10, 10, 580, 580});
    win->fill_rect({20, 20, 560, 560});
    SDL_Delay(2000);
    delete win;
    SDL_Quit();
}