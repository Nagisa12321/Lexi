#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H
#include <vector>
#include "Window.h"

class EventManager {
public:
    EventManager(Window *window);
    EventManager(const EventManager &) = delete;
    EventManager& operator=(const EventManager &) = delete;
    virtual ~EventManager();
    void add_window(Window *window);
    virtual void loop() = 0;
protected:    
    Window *m_main_window;
    Window *m_current_window;
    std::vector<Window *> m_child_windows;
};

#endif // EVENTMANAGER_H
