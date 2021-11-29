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
                                  SDL_RENDERER_ACCELERATED))
{
    // clean the screen
    SDL_SetRenderDrawColor(m_render, 230, 230, 230, 255);
    SDL_RenderFillRect(m_render, NULL);
    SDL_RenderPresent(m_render);
}

LinuxWindowImpl::~LinuxWindowImpl() {
    SDL_DestroyRenderer(m_render);
    SDL_DestroyWindow(m_window);
}

void LinuxWindowImpl::draw_line(const Point &p1, const Point &p2) {
    SDL_SetRenderDrawColor(m_render, 0, 0, 0, 255);
    SDL_RenderDrawLine(m_render, p1.x, p1.y, p2.x, p2.y);
    SDL_RenderPresent(m_render);
}

void LinuxWindowImpl::draw_rect(const WindowRect &rect) {
    SDL_SetRenderDrawColor(m_render, 0, 0, 0, 255);
    SDL_Rect r{rect.x, rect.y, rect.width, rect.height};
    SDL_RenderDrawRect(m_render, &r);
    SDL_RenderPresent(m_render);
}

void LinuxWindowImpl::fill_rect(const WindowRect &rect) {
    SDL_SetRenderDrawColor(m_render, 0, 0, 0, 255);
    SDL_Rect r{rect.x, rect.y, rect.width, rect.height};
    SDL_RenderFillRect(m_render, &r);
    SDL_RenderPresent(m_render);
}
