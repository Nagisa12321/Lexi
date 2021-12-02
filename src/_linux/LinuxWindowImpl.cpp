#include "LinuxWindowImpl.h"
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
    SDL_SetRenderDrawColor(m_render, 0xff, 0xff, 0xff, 0xff);
    SDL_RenderFillRect(m_render, NULL);
    SDL_RenderPresent(m_render);
}

LinuxWindowImpl::~LinuxWindowImpl() {
    SDL_DestroyRenderer(m_render);
    SDL_DestroyWindow(m_window);
    delete m_text_writer;
}

void LinuxWindowImpl::draw_line(const Point &p1, const Point &p2, const Color &c) {
    SDL_SetRenderDrawColor(m_render, c.R(), c.G(), c.B(), c.D());
    SDL_RenderDrawLine(m_render, p1.x, p1.y, p2.x, p2.y);
    SDL_RenderPresent(m_render);
}

void LinuxWindowImpl::draw_rect(const WindowRect &rect, const Color &c) {
    SDL_SetRenderDrawColor(m_render, c.R(), c.G(), c.B(), c.D());
    SDL_Rect r{rect.x, rect.y, rect.width, rect.height};
    SDL_RenderDrawRect(m_render, &r);
    SDL_RenderPresent(m_render);
}

void LinuxWindowImpl::fill_rect(const WindowRect &rect, const Color &c) {
    SDL_SetRenderDrawColor(m_render, c.R(), c.G(), c.B(), c.D());
    SDL_Rect r{rect.x, rect.y, rect.width, rect.height};
    SDL_RenderFillRect(m_render, &r);
    SDL_RenderPresent(m_render);
}


void LinuxWindowImpl::draw_text(const Point &p, const std::string &text, const FontSize &fs) {
    m_text_writer->write(p, text.c_str(), fs);
}

SDL_Window *LinuxWindowImpl::get_window() {
    return m_window;
}
