#include "EventManager.h"

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
