#ifndef WINDOW_H
#define WINDOW_H
#include "Types.h"
#include "Glyph.h"

class WindowImpl;
class Composition;
class Window : public Composition {
public:
    Window();
    ~Window();
    /* the copy operator is deleted */
    void draw_line(const Point &p1, const Point &p2);
    void draw_rect(const WindowRect &rect);
    void fill_rect(const WindowRect &rect);

private:    
    WindowImpl *m_window_impl;
};

class WindowImpl {
public:
    virtual void draw_line(const Point &p1, const Point &p2) = 0;
    virtual void draw_rect(const WindowRect &rect) = 0;
    virtual void fill_rect(const WindowRect &rect) = 0;
};

#endif // WINDOW_H 
