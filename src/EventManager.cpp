#include "EventManager.h"
#include "LinuxEvents.h"
#include "Window.h"
#include <stdexcept>

EventListener::EventListener(Window *window)
    : m_main_window(window),
      m_current_window(window),
      m_child_windows()
{

}

EventListener::~EventListener() {
    delete m_main_window;
    for (Window *window : m_child_windows)
        delete window;
}


void EventListener::add_window(Window *window) {
    m_current_window = window;
    m_child_windows.push_back(window);
}

EventListener *EventListener::manager;

void EventListener::init_listener(const GuiFactory::OS &os, Window *win, int fps) {
    if (os == GuiFactory::OS::Linux) {
        // static LinuxEventManager linux_event(win, fps);
        // manager = &linux_event;
        manager = new LinuxEventListener(win, fps);
    }
    else lexi_abort("unspport os.\n");
}

EventListener *EventListener::get_listener() {
    return manager;
}

void EventListener::destory_listener() {
    manager->stop();
    delete manager;
}


void RenderExecutor::init_executor() {
    exec = new RenderExecutor();
}
RenderExecutor *RenderExecutor::get_executor() {
    return exec;
}
void RenderExecutor::destory_executor() {
    exec->stop();
    delete exec;
}

void EventExecutor::init_executor(int threads) {
    exec = new EventExecutor(threads);
}
EventExecutor *EventExecutor::get_executor() {
    return exec;
}
void EventExecutor::destory_executor() {
    exec->stop();
    delete exec;
}
EventExecutor *EventExecutor::exec = 0;
RenderExecutor *RenderExecutor::exec = 0;
