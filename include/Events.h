#ifndef EVENTS_H
#define EVENTS_H
#include "Types.h"

enum EventType {
};

class Event {
public:
    Event(const Point &p, const EventType &type);
    Event(const Event &) = delete;
    virtual ~Event() = default;
    Event &operator=(const Event &) = delete;

    const EventType &get_event_type() const;
    const Point &get_event_point() const;
private:
    Point m_event_point;
    EventType m_event_type;
};

#endif // EVENTS_H
