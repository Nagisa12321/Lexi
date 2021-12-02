#include "Events.h"

Event::Event(const Point &p, const EventType &type) :
    m_event_type(type),
    m_event_point(p) {
}


const Point &Event::get_event_point() const {
	return m_event_point;
}

MousePressEvent::MousePressEvent(const Point &p, bool down) 
    : Event(p, EventType::Event_MousePressEvent),
      m_down(down)
{

}

bool MousePressEvent::down() const { return m_down; }
