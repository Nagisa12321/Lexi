#ifndef GUIFACTORY_H
#define GUIFACTORY_H
#include <string>
#include "Original.h"
#include "Window.h"
#include "Utils.h"

class GuiFactory {
public:
    enum OS {
        Linux, 
    };
    GuiFactory() = default;
    GuiFactory(const GuiFactory &) = delete;
    virtual ~GuiFactory() = default;
    GuiFactory &operator=(const GuiFactory &) = delete;

    Window *create_window(const WindowRect &rect, const std::string &name);
    virtual Button *create_button(const WindowRect &rect, const std::string &name)  = 0;
    virtual WindowImpl *create_window_impl(const WindowRect &rect, const char *title) = 0;

    static GuiFactory *get_factory();
    static void set_factory(const GuiFactory::OS &os);
public:
    static GuiFactory *real_factory;
};

#endif // GUIFACTORY_H
