#ifndef LINUXGUIFACTORY_H
#define LINUXGUIFACTORY_H
#include "GuiFactory.h"

class GuiFactory;
class LinuxGuiFactory : public GuiFactory {
public:
    Button *create_button(const WindowRect &rect, const std::string &name) override;
    WindowImpl *create_window_impl(const WindowRect &rect, const char *title) override;
};

#endif // LINUXGUIFACTORY_H
