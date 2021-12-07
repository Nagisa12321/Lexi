#include "Commands.h"
#include "EventManager.h"
#include "LinuxCommands.h"
#include "Logger.h"
#include "Original.h"
#include "Window.h"
#include "SDL.h"
#include "SDL_ttf.h"
#include "GuiFactory.h"
#include "LinuxOriginal.h"
#include <iostream>
#include <ostream>
#include <thread>

using namespace std;

int main() {
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();

    // init gui factory
    GuiFactory::init_factory(GuiFactory::OS::Linux);
    BlockingQueueManager::init_manager();

    Window *main_window = GuiFactory::get_factory()->create_window({100, 100, 400, 400}, "main window");
    EventListener::init_listener(GuiFactory::OS::Linux, main_window, 60);


    Button *button1 = GuiFactory::get_factory()->create_button({100, 300, 200, 80}, "this is a button");
    button1->add_press_handler([] {
        cout << "I am pressed!" << endl;
    });
    button1->add_release_handler([] {
        cout << "I am released!" << endl;
    });
    main_window->add(button1);
    main_window->draw(main_window); 

    bool running = true;
    QuitCommand *quit = new QuitCommand(&running); 
    EventListener::get_listener()->loop();
    Command *c;
    for (; running;) {
        c = BlockingQueueManager::get_manager()->get_randering_queue()->take();
        c->exec(); 
        delete c;
    }
    Logger::get_logger()->debug("end the randerer loop. \n");
    EventListener::destory_listener();
    BlockingQueueManager::destory_manager();
    TTF_Quit();
    SDL_Quit();
}