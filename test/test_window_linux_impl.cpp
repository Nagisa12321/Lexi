#include "SDL.h"
#include "LinuxWindowImpl.h"
#include <iostream>

using namespace std;

int main() {
    SDL_Init(SDL_INIT_EVERYTHING);
    LinuxWindowImpl *impl1 = new LinuxWindowImpl({10, 10, 500, 500}, "test windows1");
    LinuxWindowImpl *impl2 = new LinuxWindowImpl({510, 10, 500, 500}, "test windows2");
    LinuxWindowImpl *impl3 = new LinuxWindowImpl({1010, 10, 500, 500}, "test windows2");
    SDL_Delay(1000);
    delete impl1;
    delete impl2;
    delete impl3;
    SDL_Quit();
}