#ifndef LINUXEVENTS_H
#define LINUXEVENTS_H
#include "EventManager.h"

class LinuxEventManager : public EventManager {
    friend class EventManager;
public:
    void loop() override;
    void stop() override;

private:
    LinuxEventManager(Window *window, int fps);
    int m_fps;
    bool m_running;
    bool m_stopped;
};

#endif // LINUXEVENTS_H
