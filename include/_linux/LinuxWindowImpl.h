#ifndef LINUXWINDOWIMPL_H
#define LINUXWINDOWIMPL_H
#include "Window.h"
#include "SDL2/SDL.h"

class LinuxWindowImpl : public WindowImpl {
public:
    LinuxWindowImpl(const WindowRect &rect, const char *title);
    ~LinuxWindowImpl();

    void draw_line(const Point &p1, const Point &p2) override;
    void draw_rect(const WindowRect &rect) override;
    void fill_rect(const WindowRect &rect) override;

private:
    SDL_Window *m_window;
    SDL_Renderer *m_render;
};


#endif // LINUXWINDOWIMPL_H
