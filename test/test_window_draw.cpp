#include "SDL2/SDL.h"
#include "LinuxWindowImpl.h"
#include "LinuxOriginal.h"

int main() {
    SDL_Init(SDL_INIT_EVERYTHING);
    WindowImpl *impl = new LinuxWindowImpl({10, 10, 600, 600}, "test draw");
    impl->draw_rect({10, 10, 580, 580}, LinuxColor{0x0, 0x0, 0x0, 0xff});
    impl->fill_rect({20, 20, 560, 560}, LinuxColor{0x0, 0x0, 0x0, 0xff});
    SDL_Delay(2000);
    SDL_Quit();
}