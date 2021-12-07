#include "LinuxOriginal.h"
#include "GuiFactory.h"
#include "Window.h"
#include "Events.h"
#include "Utils.h"
#include "Types.h"
#include "LinuxWriter.h"
#include "Events.h"
#include <cstdio>

using namespace std;

const SDL_Color button_default_color        = {0xdf, 0xdf, 0xdf, 0xff};
const SDL_Color button_default_frame_color  = {0x00, 0x00, 0x00, 0xff};
const SDL_Color button_pressed_color        = {0xaa, 0xaa, 0xaa, 0xff};

LinuxButton::LinuxButton(const WindowRect &rect, const std::string &name) 
    : Button(rect, name),
      m_down(false)
{

}

void LinuxButton::draw(Window *w) {
    if (m_down) { draw_pressed(w); }
    else { draw_normal(w); }

}

void LinuxButton::draw_normal(Window *w) {
    int text_width = m_name.size() * linux_min_font_size / 2;
    int x_start = (m_rect.width - text_width) / 2;
    int y_start = (m_rect.height - linux_min_font_size) / 2;
    w->fill_rect(this->m_rect, LinuxColor(button_default_color));
    w->draw_rect(this->m_rect, LinuxColor(button_default_frame_color));
    w->draw_text({m_rect.x + x_start, m_rect.y + y_start}, m_name, FontSize::min);
}

void LinuxButton::draw_pressed(Window *w) {
    int text_width = m_name.size() * linux_min_font_size / 2;
    int x_start = (m_rect.width - text_width) / 2;
    int y_start = (m_rect.height - linux_min_font_size) / 2;
    w->fill_rect(this->m_rect, LinuxColor(button_pressed_color));
    w->draw_rect(this->m_rect, LinuxColor(button_default_frame_color));
    w->draw_text({m_rect.x + x_start, m_rect.y + y_start}, m_name, FontSize::min);
}



void LinuxButton::process_event(const Event &event) {
    const MousePressEvent &e = dynamic_cast<const MousePressEvent &>(event);
    if (intersects(e.get_event_point())) {
        if (e.down()) { m_down = true; m_press_handler(); }
        else { m_down = false; m_release_handler(); }   
    }

}

void LinuxButton::insert(Glyph *child, int index) {
    lexi_abort("unspprted operation!\n");
}

void LinuxButton::add(Glyph *child) {
    lexi_abort("unspprted operation!\n");
}

void LinuxButton::remove(Glyph *child) {
    lexi_abort("unspprted operation!\n");
}

Glyph *LinuxButton::child(int index) {
    lexi_abort("unspprted operation!\n");
    return 0;
}

Glyph *LinuxButton::parent() {
    lexi_abort("unspprted operation!\n");
    return 0;
}
