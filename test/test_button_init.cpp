#include "Original.h"
#include "Window.h"
#include "SDL.h"
#include "SDL_ttf.h"
#include "LinuxOriginal.h"

int main() {
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();

    Window *win1 = new Window({100, 100, 300, 300}, "test draw text");
    win1->draw_text({100, 100}, "hello wolrd!", FontSize::mid);
    
    Button *b = new LinuxButton({100, 200, 100, 50}, "button");
    win1->add(b);

    win1->draw(win1);

    SDL_Delay(3000);
    delete win1;

    TTF_Quit();
    SDL_Quit();
}