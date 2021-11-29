#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H
#include "Window.h"

class EventManager {
public:
    virtual void loop() = 0;
protected:    
    Window *m_window;
};

#endif // EVENTMANAGER_H
