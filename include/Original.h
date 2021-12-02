#ifndef ORIGINAL_H
#define ORIGINAL_H
#include <string>
#include "Glyph.h"

class Glyph;
class Button : public Glyph {
public:
    Button(const WindowRect &rect, const std::string &name);
    ~Button() = default;
protected:
    std::string m_name;
    bool m_pressed;
};

#endif // ORIGINAL_H
