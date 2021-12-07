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
    RenderExecutor::init_executor();
    EventExecutor::init_executor(1);

    Window *main_window = GuiFactory::get_factory()->create_window({100, 100, 400, 400}, "main window");
    EventListener::init_listener(GuiFactory::OS::Linux, main_window, 60);

    Button *button1 = GuiFactory::get_factory()->create_button({100, 300, 200, 80}, "this is a button");
    button1->add_press_handler([] {
        cout << "I am pressed!" << endl;
        GuiFactory *factory = GuiFactory::get_factory();
        int res = factory->open_tips_window(GuiFactory::TipsWindowType::Ok, 0, 0, "test tip", "hello world!"); 
        if (res) cout << "the result is --- yes" << endl;
        else cout << "the result is --- no" << endl;
    });
    main_window->add(button1);
    main_window->draw(main_window); 

    EventListener::get_listener()->loop();
    EventExecutor::get_executor()->start();
    RenderExecutor::get_executor()->start();

    EventListener::destory_listener();
    EventExecutor::destory_executor();
    BlockingQueueManager::destory_manager();
    TTF_Quit();
    SDL_Quit();
}