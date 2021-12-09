#include "SDL.h"
#include "SDL_timer.h"
#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

int main() {
    SDL_Init(SDL_INIT_EVERYTHING);

    mutex m;
    bool running = true;
    auto run = [&] {
        while (running) {
            SDL_Event event;
            int x, y;
            for (;;) {
                int __tmp;
                {
                    unique_lock<mutex> __lk(m);
                    __tmp = SDL_PollEvent(&event);
                }
                if (!__tmp)
                    break;

                if (event.type == SDL_QUIT) {
                    cout << "SDL_QUIT" << endl;
                    running = false;
                    break;
                }
            }
            SDL_Delay(10);
        }
    };

    thread t(run);
    for (int i = 0; i < 10; ++i) {
        {
            unique_lock<mutex> __lk(m);
            SDL_Window *window = SDL_CreateWindow("cycle. ", 
                                                100,
                                                100,
                                                600,
                                                600,
                                                SDL_WINDOW_SHOWN);

            SDL_Renderer *screen = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        }
    }
    SDL_Delay(5000);

    running = false;
    t.join();
    SDL_Quit();
}