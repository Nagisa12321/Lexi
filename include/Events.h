#ifndef EVENTS_H
#define EVENTS_H
#include "Types.h"

enum EventType {
    Event_MousePressEvent,
};

class Event {
public:
    Event(const Point &p, const EventType &type);
    virtual ~Event() = default;

    const EventType &get_event_type() const;
    const Point &get_event_point() const;
private:
    Point m_event_point;
    EventType m_event_type;
};

class MousePressEvent : public Event {
public:
    MousePressEvent(const Point &p, bool down);
    bool down() const;
private:
    bool m_down;
};
#endif // EVENTS_H
