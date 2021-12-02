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

    GuiFactory::set_factory(GuiFactory::OS::Linux);
    GuiFactory *fatory = GuiFactory::get_factory();
    Window *window = fatory->create_window({100, 100, 400, 400}, "test window1");
    
    Button *button = fatory->create_button({100, 300, 200, 80}, "this is a button");
    window->add(button);
    window->draw(window);
    EventManager *manager = new LinuxEventManager(window, 60);

    manager->loop();
    delete manager;
    TTF_Quit();
    SDL_Quit(); 
}   