#ifndef WINDOW_H
#define WINDOW_H
#include <string> 
#include "Logger.h"
#include "Types.h"
#include "Glyph.h"
#include "Commands.h"


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
    void draw_cycle(const Point &p, int radius, const Color &c);
    void fill_cycle(const Point &p, int radius, const Color &c);
    void add(Glyph *child) override;

    WindowImpl *get_impl();
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
    virtual void draw_cycle(const Point &p, int radius, const Color &c) = 0;
    virtual void fill_cycle(const Point &p, int radius, const Color &c) = 0;
};

class CreateWindow : public Command {
public:
    CreateWindow(const WindowRect &rect, const std::string &topic)
        : Command("create window"),
          m_rect(rect),
          m_topic(topic)
    {

    }
    void exec() override {
        Command::exec();
        Window *win = new Window(m_rect, m_topic.c_str());
        Logger::get_logger()->debug("create window %p\n", win);
        BlockingQueueManager::get_manager()->get_new_window_queue()->put(win);
    }
    ~CreateWindow() = default;
private:
    WindowRect  m_rect;
    std::string      m_topic;
};

class DeleteWindow : public Command {
public:
    DeleteWindow()
        : Command("delete window")
    {

    }
    void exec() override {
        Command::exec();
        Window *window = BlockingQueueManager::get_manager()->get_delete_window_queue()->take();
        Logger::get_logger()->debug("delete window %p\n", window);
        delete window;
    }
    ~DeleteWindow() = default;
private:
    WindowRect  m_rect;
    std::string      m_topic;
};

void __delete_window(Window *win);

#endif // WINDOW_H 
