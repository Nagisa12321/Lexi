#include "EventManager.h"
#include "GuiFactory.h"
#include "LinuxEvents.h"
#include "SDL.h"
#include "SDL_ttf.h"
#include "Window.h"

int main() {
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();

    GuiFactory::set_factory(GuiFactory::OS::Linux);
    GuiFactory *fatory = GuiFactory::get_factory();
    Window *window = fatory->create_window({100, 100, 400, 400}, "test window1");
    EventManager *manager = new LinuxEventManager(window, 60);

    manager->add_window(fatory->create_window({500, 100, 400, 400}, "test window2"));
    manager->loop();
    delete manager;
    TTF_Quit();
    SDL_Quit(); 
}   