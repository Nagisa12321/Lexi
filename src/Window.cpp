#include "Window.h"
#include "LinuxWindowImpl.h"
using namespace std;

Window::Window(const WindowRect &rect, const char *title)
    : Composition(rect, nullptr),
      m_window_impl(new LinuxWindowImpl(rect, title))
{

}

Window::~Window() {
    delete m_window_impl;
}

void Window::draw_line(const Point &p1, const Point &p2) {
    m_window_impl->draw_line(p1, p2);
}

void Window::draw_rect(const WindowRect &rect) {
    m_window_impl->draw_rect(rect);
}

void Window::fill_rect(const WindowRect &rect) {
    m_window_impl->fill_rect(rect);
}

WindowImpl::~WindowImpl() {}