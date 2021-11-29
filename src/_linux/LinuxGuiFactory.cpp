#include "LinuxOriginal.h"
#include "LinuxWindowImpl.h"
#include "Window.h"
#include "GuiFactory.h"
#include "LinuxGuiFactory.h"

Button *LinuxGuiFactory::create_button(const WindowRect &rect, const std::string &name) {
    return new LinuxButton(rect, name);
}

WindowImpl *LinuxGuiFactory::create_window_impl(const WindowRect &rect, const char *title) {
    return new LinuxWindowImpl(rect, title);
}

