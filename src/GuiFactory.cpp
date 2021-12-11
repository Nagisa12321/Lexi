#include "GuiFactory.h"
#include "Commands.h"
#include "EventManager.h"
#include "LinuxCommands.h"
#include "LinuxGuiFactory.h"
#include "LinuxOriginal.h"
#include "Logger.h"
#include "Original.h"
#include "Types.h"
#include "Commands.h"
#include "Window.h"
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <unistd.h>

using namespace std;

std::mutex m;

GuiFactory *GuiFactory::get_factory() {
    if (!real_factory) { lexi_abort("you have not set the GUI factory!\n"); }
    return real_factory;
}

void GuiFactory::init_factory(const GuiFactory::OS &os) {
    if (os == OS::Linux) {
        // static LinuxGuiFactory lgf;
        // real_factory = &lgf;
        real_factory = new LinuxGuiFactory();
    } 

    else lexi_abort("unspport os.\n");
}

GuiFactory *GuiFactory::real_factory = nullptr;


Window *GuiFactory::create_window(const WindowRect &rect, const std::string &name) {
    return new Window(rect, name.c_str());
}


Window *GuiFactory::open_window(const WindowRect &rect, const std::string &name) {
    BlockingQueueManager *manager = BlockingQueueManager::get_manager();
    Command *task = new CreateWindow(rect, name);
    Logger::get_logger()->debug("put a CreateWindow task %p. \n", task);
    manager->get_randering_queue()->put(task);
    Window *window = manager->get_new_window_queue()->take();
    Logger::get_logger()->debug("get a new window. \n");
    return window;
}

static int __open_ok_window(Window *tips_window, const std::string &text) {
    tips_window->fill_cycle({60, 40}, 20, LinuxColor{0, 255, 0, 255});
    tips_window->draw_cycle({60, 40}, 20, LinuxColor{0, 0, 0, 255});
    tips_window->draw_text({120, 30}, text, FontSize::min);

    // yes
    tips_window->draw_line({52, 43}, {60, 53}, LinuxColor{0, 0, 0, 255});
    tips_window->draw_line({70, 30}, {60, 53}, LinuxColor{0, 0, 0, 255});

    // button
    Button *__yes = GuiFactory::get_factory()->create_button({100, 80, 50, 20}, "yes");
    Button *__no = GuiFactory::get_factory()->create_button({200, 80, 50, 20}, "no");

    int __res;
    mutex __m;
    condition_variable __cv;
    unique_lock<mutex> __lk(__m);

    __yes->add_press_handler([&] { 
        cout << "yes!" << endl; 
        __res = 1;
        __cv.notify_all();
    });
    __no->add_press_handler([&] { 
        cout << "no!" << endl; 
        __res = 0;
        __cv.notify_all();
    });
    tips_window->add(__yes);
    tips_window->add(__no);
    __cv.wait(__lk);
    
    EventListener::get_listener()->close_window(tips_window);
    
    return __res;
}

int GuiFactory::open_tips_window(const TipsWindowType &type, 
                                 const WindowRect *rect, 
                                 const WindowRect *parent_rect, 
                                 const std::string &name, 
                                 const std::string &text) {
    int tips_width = 300;
    int tips_height = 120;
    WindowRect real_rect;
    if (!rect) {
        if (!parent_rect) {
            real_rect = {500, 500, tips_width, tips_height};
        } else {
            int tips_x, tips_y;
            tips_x = parent_rect->x + ((parent_rect->width - tips_width) >> 1);
            tips_y = parent_rect->y + ((parent_rect->height - tips_height) >> 1);
            real_rect = {tips_x, tips_y, tips_width, tips_height};
        }
    } else { real_rect = *parent_rect; }

    Window *tips_window = open_window(real_rect, name);

    EventListener::get_listener()->add_window(tips_window);
    if (type == TipsWindowType::Ok)
        return __open_ok_window(tips_window, text);
    
    return 1;
}
