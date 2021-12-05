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
    enum TipsWindowType {
        Error,
        Ok,
        Warnning,
    };
    GuiFactory() = default;
    GuiFactory(const GuiFactory &) = delete;
    virtual ~GuiFactory() = default;
    GuiFactory &operator=(const GuiFactory &) = delete;

    Window *create_window(const WindowRect &rect, const std::string &name);
    int open_tips_window(const TipsWindowType &type, const WindowRect *rect, const WindowRect *parent_rect, const std::string &name = "", const std::string &text = "text");
    virtual Button *create_button(const WindowRect &rect, const std::string &name)  = 0;
    virtual WindowImpl *create_window_impl(const WindowRect &rect, const char *title) = 0;

    static GuiFactory *get_factory();
    static void init_factory(const GuiFactory::OS &os);
public:
    static GuiFactory *real_factory;
};

#endif // GUIFACTORY_H
