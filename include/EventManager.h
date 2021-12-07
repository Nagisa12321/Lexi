#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H
#include <vector>
#include "GuiFactory.h"
#include "Window.h"
#include "Commands.h"

class EventManager {
public:
    static void init_manager(const GuiFactory::OS &os, Window *win, int fps);
    static EventManager *get_manager();
    static void destory_manager();
    EventManager(const EventManager &) = delete;
    EventManager& operator=(const EventManager &) = delete;
    virtual ~EventManager();
    virtual void loop(QuitCommand *quit) = 0;
    virtual void stop() = 0;
    void add_window(Window *window);
protected:    
    EventManager(Window *window);
    Window *m_main_window;
    Window *m_current_window;
    std::vector<Window *> m_child_windows;

private:
    static EventManager *manager;
};

#endif // EVENTMANAGER_H
