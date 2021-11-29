#ifndef LINUXEVENTS_H
#define LINUXEVENTS_H
#include "EventManager.h"

class LinuxEventManager : public EventManager {
public:
    void loop() override;
};

#endif // LINUXEVENTS_H
