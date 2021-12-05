#include "GuiFactory.h"
#include "LinuxGuiFactory.h"
#include "Types.h"
#include "Window.h"

GuiFactory *GuiFactory::get_factory() {
    if (!real_factory) { lexi_abort("you have not set the GUI factory!\n"); }
    return real_factory;
}

void GuiFactory::init_factory(const GuiFactory::OS &os) {
    if (os == OS::Linux) {
        // static LinuxGuiFactory lgf;
        // real_factory = &lgf;
        real_factory = new LinuxGuiFactory();
    } 

    else lexi_abort("unspport os.\n");
}

GuiFactory *GuiFactory::real_factory = nullptr;


Window *GuiFactory::create_window(const WindowRect &rect, const std::string &name) {
    return new Window(rect, name.c_str());
}

// static int open_ok_window() {

// }

int GuiFactory::open_tips_window(const TipsWindowType &type, 
                                 const WindowRect *rect, 
                                 const WindowRect *parent_rect, 
                                 const std::string &name, 
                                 const std::string &text) {
    int tips_width = 500;
    int tips_height = 300;
    WindowRect real_rect;
    if (!rect) {
        if (!parent_rect) {
            real_rect = {500, 500, tips_width, tips_height};
        } else {
            int tips_x, tips_y;
            tips_x = parent_rect->x + ((parent_rect->width - tips_width) >> 1);
            tips_y = parent_rect->y + ((parent_rect->height - tips_height) >> 1);
            real_rect = {tips_x, tips_y, tips_width, tips_height};
        }
    } else { real_rect = *parent_rect; }

    Window *tips_window = create_window(real_rect, name);
    return 1;
}
