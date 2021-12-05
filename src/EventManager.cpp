#include "EventManager.h"
#include "LinuxEvents.h"
#include "Window.h"
#include <stdexcept>

EventManager::EventManager(Window *window)
    : m_main_window(window),
      m_current_window(window),
      m_child_windows()
{

}

EventManager::~EventManager() {
    delete m_main_window;
    for (Window *window : m_child_windows)
        delete window;
}


void EventManager::add_window(Window *window) {
    m_child_windows.push_back(window);
}

EventManager *EventManager::manager;

void EventManager::init_manager(const GuiFactory::OS &os, Window *win, int fps) {
    if (os == GuiFactory::OS::Linux) {
        // static LinuxEventManager linux_event(win, fps);
        // manager = &linux_event;
        manager = new LinuxEventManager(win, fps);
    }
    else lexi_abort("unspport os.\n");
}

EventManager *EventManager::get_manager() {
    return manager;
}

void EventManager::destory_manager() {
    manager->stop();
    delete manager;
}
