#include "Window.h"
#include "LinuxWindowImpl.h"
#include "GuiFactory.h"
using namespace std;

Window::Window(const WindowRect &rect, const char *title)
    : Composition(rect, nullptr),
      m_window_impl(GuiFactory::get_factory()->create_window_impl(rect, title))
{

}

Window::~Window() {
    delete m_window_impl;
}

void Window::draw_line(const Point &p1, const Point &p2, const Color &c) {
    m_window_impl->draw_line(p1, p2, c);
}

void Window::draw_rect(const WindowRect &rect, const Color &c) {
    m_window_impl->draw_rect(rect, c);
}

void Window::fill_rect(const WindowRect &rect, const Color &c) {
    m_window_impl->fill_rect(rect, c);
}

void Window::draw_text(const Point &p, const std::string &text, const FontSize &fs) {
    m_window_impl->draw_text(p, text, fs);
}


WindowImpl::~WindowImpl() {}