#include "LinuxWindowImpl.h"
#include "Commands.h"
#include "LinuxCommands.h"
#include <cstdio>
using namespace std;

LinuxWindowImpl::LinuxWindowImpl(const WindowRect &rect, const char *title)
    : WindowImpl(),
      m_window(SDL_CreateWindow(title, 
                                rect.x, 
                                rect.y,
                                rect.width,
                                rect.height, 
                                SDL_WINDOW_SHOWN)),
      m_render(SDL_CreateRenderer(m_window, 
                                  -1, 
                                  SDL_RENDERER_ACCELERATED)),
      m_text_writer(new LinuxWriter("../ttfs/UbuntuMono.ttf", m_render))
{
    // clean the screen
    CommandQueueManager::get_manager()->get_randering_queue()->put(new CleanScreen(m_render));
}

LinuxWindowImpl::~LinuxWindowImpl() {
    SDL_DestroyRenderer(m_render);
    SDL_DestroyWindow(m_window);
    delete m_text_writer;
}

void LinuxWindowImpl::draw_line(const Point &p1, const Point &p2, const Color &c) {
    CommandQueueManager::get_manager()->get_randering_queue()->put(new DrawLine(m_render, p1, p2, c));
}

void LinuxWindowImpl::draw_rect(const WindowRect &rect, const Color &c) {
    CommandQueueManager::get_manager()->get_randering_queue()->put(new DrawRect(m_render, rect, c));
}

void LinuxWindowImpl::fill_rect(const WindowRect &rect, const Color &c) {
    CommandQueueManager::get_manager()->get_randering_queue()->put(new FillRect(m_render, rect, c));
}

void LinuxWindowImpl::draw_text(const Point &p, const std::string &text, const FontSize &fs) {
    CommandQueueManager::get_manager()->get_randering_queue()->put(new DrawText(m_text_writer, p, text, fs));
}

SDL_Window *LinuxWindowImpl::get_window() {
    return m_window;
}
