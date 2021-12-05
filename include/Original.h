#ifndef ORIGINAL_H
#define ORIGINAL_H
#include <string>
#include <functional>
#include "Glyph.h"

class Glyph;
class Button : public Glyph {
public:
    Button(const WindowRect &rect, const std::string &name);
    ~Button() = default;

    void add_press_handler(const std::function<void()> &fn);
    void add_release_handler(const std::function<void()> &fn);
protected:
    std::function<void()> m_press_handler;
    std::function<void()> m_release_handler;
    std::string m_name;
    bool m_pressed;
};

#endif // ORIGINAL_H
