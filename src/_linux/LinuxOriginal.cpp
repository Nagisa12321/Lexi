#include "LinuxOriginal.h"
#include "Window.h"
#include "Events.h"
#include "Utils.h"
#include "Types.h"
#include "LinuxWriter.h"

using namespace std;

const SDL_Color button_default_color = {0xdf, 0xdf, 0xdf, 0xff};;
const SDL_Color button_pressed_color = {0xcc, 0xcc, 0xcc, 0xff};

LinuxButton::LinuxButton(const WindowRect &rect, const std::string &name) 
    : Button(rect, name)
{

}

void LinuxButton::draw(Window *w) {
    int text_width = m_name.size() * linux_min_font_size / 2;
    int x_start = (m_rect.width - text_width) / 2;
    int y_start = (m_rect.height - linux_min_font_size) / 2;
    w->fill_rect(this->m_rect, LinuxColor(button_default_color));
    w->draw_text({m_rect.x + x_start, m_rect.y + y_start}, m_name, FontSize::min);
}

void LinuxButton::process_event(const Event &event) {
    
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
