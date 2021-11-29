#ifndef WINDOW_H
#define WINDOW_H
#include <string> 
#include "Types.h"
#include "Glyph.h"

class WindowImpl;
class Composition;

class Window : public Composition {
public:
    Window(const WindowRect &rect, const char *title);
    ~Window();
    /* the copy operator is deleted */
    void draw_line(const Point &p1, const Point &p2, const Color &c);
    void draw_rect(const WindowRect &rect, const Color &c);
    void fill_rect(const WindowRect &rect, const Color &c);
    void draw_text(const Point &p, const std::string &text, const FontSize &fs);
private:    
    WindowImpl *m_window_impl;
};

class WindowImpl {
public:
    WindowImpl() = default;
    virtual ~WindowImpl() = 0;
    virtual void draw_line(const Point &p1, const Point &p2, const Color &c) = 0;
    virtual void draw_rect(const WindowRect &rect, const Color &c) = 0;
    virtual void fill_rect(const WindowRect &rect, const Color &c) = 0;
    virtual void draw_text(const Point &p, const std::string &text, const FontSize &fs) = 0;
};

#endif // WINDOW_H 
