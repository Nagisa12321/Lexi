#include "GuiFactory.h"
#include "LinuxGuiFactory.h"

GuiFactory *GuiFactory::get_factory() {
    if (!real_factory) { lexi_abort("you have not set the GUI factory!\n"); }
    return real_factory;
}

void GuiFactory::set_factory(const GuiFactory::OS &os) {
    if (os == OS::Linux) real_factory = new LinuxGuiFactory();

    else lexi_abort("unspport os.\n");
}

GuiFactory *GuiFactory::real_factory = nullptr;
