#ifndef LINUXEVENTS_H
#define LINUXEVENTS_H
#include "Commands.h"
#include "EventManager.h"
#include <thread>

class LinuxEventListener : public EventListener {
    friend class EventListener;
public:
    void loop() override;
    void stop() override;

private:
    LinuxEventListener(Window *window, int fps);
    int m_fps;
    bool m_running;
    bool m_stopped;
    std::thread m_event_thread;
};

#endif // LINUXEVENTS_H
