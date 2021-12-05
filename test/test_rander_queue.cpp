#include "Commands.h"
#include "EventManager.h"
#include "Original.h"
#include "Window.h"
#include "SDL.h"
#include "SDL_ttf.h"
#include "GuiFactory.h"
#include "LinuxOriginal.h"
#include <iostream>
#include <ostream>
#include <thread>

int main() {
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();

    // init gui factory
    GuiFactory::init_factory(GuiFactory::OS::Linux);
    CommandQueueManager::init_manager();

    Window *main_window = GuiFactory::get_factory()->create_window({100, 100, 400, 400}, "main window");
    EventManager::init_manager(GuiFactory::OS::Linux, main_window, 60);

    Button *button1 = GuiFactory::get_factory()->create_button({100, 300, 200, 80}, "this is a button");
    main_window->add(button1);
    main_window->draw(main_window); 

    auto drawer = [] {
        Command *c;
        for (;;) {
            c = CommandQueueManager::get_manager()->get_randering_queue()->take();
            if (c) { c->exec(); delete c; }
            else break;
        }
    };

    std::thread t1(drawer);
    EventManager::get_manager()->loop();

    EventManager::destory_manager();
    CommandQueueManager::get_manager()->get_randering_queue()->clear();

    t1.join();

    CommandQueueManager::destory_manager();
    TTF_Quit();
    SDL_Quit();
}