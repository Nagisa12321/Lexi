#include "Window.h"

void Window::draw_line(const Point &p1, const Point &p2) {
    m_window_impl->draw_line(p1, p2);
}

void Window::draw_rect(const WindowRect &rect) {
    m_window_impl->draw_rect(rect);
}

void Window::fill_rect(const WindowRect &rect) {
    m_window_impl->fill_rect(rect);
}


