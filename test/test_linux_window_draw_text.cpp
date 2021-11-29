#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "Window.h"
#include <iostream>

using namespace std;

int main() {
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();

    Window *win1 = new Window({100, 100, 300, 300}, "test draw text");
    win1->draw_text({100, 100}, "hello wolrd!", FontSize::mid);
    SDL_Delay(3000);
    delete win1;

    TTF_Quit();
    SDL_Quit();
}