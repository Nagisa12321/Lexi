#ifndef LINUXWINDOWIMPL_H
#define LINUXWINDOWIMPL_H
#include "Window.h"
#include "SDL.h"
#include "LinuxWriter.h"
#include "Types.h"

class LinuxWindowImpl : public WindowImpl {
public:
    LinuxWindowImpl(const WindowRect &rect, const char *title);
    ~LinuxWindowImpl();

    void draw_line(const Point &p1, const Point &p2, const Color &c) override;
    void draw_rect(const WindowRect &rect, const Color &c) override;
    void fill_rect(const WindowRect &rect, const Color &c) override;
    void draw_text(const Point &p, const std::string &text, const FontSize &fs) override;
    void draw_cycle(const Point &p, int radius, const Color &c) override;
    void fill_cycle(const Point &p, int radius, const Color &c) override;
    SDL_Window *get_window();
private:
    SDL_Window      *m_window;
    SDL_Renderer    *m_render;
    LinuxWriter     *m_text_writer;
};


#endif // LINUXWINDOWIMPL_H
