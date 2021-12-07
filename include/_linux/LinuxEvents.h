#ifndef LINUXEVENTS_H
#define LINUXEVENTS_H
#include "Commands.h"
#include "EventManager.h"
#include <thread>

class LinuxEventManager : public EventManager {
    friend class EventManager;
public:
    void loop(QuitCommand *quit) override;
    void stop() override;

private:
    LinuxEventManager(Window *window, int fps);
    int m_fps;
    bool m_running;
    bool m_stopped;
    std::thread m_event_thread;
};

#endif // LINUXEVENTS_H
