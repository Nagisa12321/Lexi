#ifndef LINUXWINDOWIMPL_H
#define LINUXWINDOWIMPL_H
#include "Window.h"

class LinuxWindowImpl : public WindowImpl {
public:
    LinuxWindowImpl();
    ~LinuxWindowImpl();

    void draw_line(const Point &p1, const Point &p2);
    void draw_rect(const WindowRect &rect);
    void fill_rect(const WindowRect &rect);
};


#endif // LINUXWINDOWIMPL_H
