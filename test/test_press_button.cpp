#include "EventManager.h"
#include "GuiFactory.h"
#include "LinuxEvents.h"
#include "Original.h"
#include "SDL.h"
#include "SDL_ttf.h"
#include "Window.h"

int main() {
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();

    GuiFactory::init_factory(GuiFactory::OS::Linux);
    GuiFactory *factory = GuiFactory::get_factory();
    Window *win1 = factory->create_window({100, 100, 400, 400}, "main window");
    Window *win2 = factory->create_window({150, 150, 400, 400}, "test window 2");
    
    Button *button1 = factory->create_button({100, 300, 200, 80}, "this is a button");
    Button *button2 = factory->create_button({100, 300, 200, 80}, "this is a button too");
    win1->add(button1);
    win2->add(button2);
    win1->draw(win1);
    win2->draw(win2);
    EventManager::init_manager(GuiFactory::OS::Linux, win1, 60);
    EventManager *manager = EventManager::get_manager();
    manager->add_window(win2);

    bool running = true;
    QuitCommand *quit = new QuitCommand(&running); 
    manager->loop(quit);
    delete factory;
    delete manager;

    TTF_Quit();
    SDL_Quit(); 
}   