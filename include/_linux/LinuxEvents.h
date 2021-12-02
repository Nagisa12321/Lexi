#ifndef LINUXEVENTS_H
#define LINUXEVENTS_H
#include "EventManager.h"

class LinuxEventManager : public EventManager {
public:
    LinuxEventManager(Window *window, int fps);
    void loop() override;

private:
    int m_fps;
};

#endif // LINUXEVENTS_H
