#ifndef LINUXORIGINAL_H
#define LINUXORIGINAL_H
#include "Original.h"
#include "SDL2/SDL.h"
#include "Types.h"

extern const SDL_Color button_default_color;
extern const SDL_Color button_pressed_color;

class Button;
class LinuxButton : public Button {
public:
    LinuxButton(const WindowRect &rect, const std::string &name);

    void draw(Window *w) override;
    void process_event(const Event &event) override;

    // unspported
    void insert(Glyph *child, int index) override;
    void add(Glyph *child) override;
    void remove(Glyph *child) override;
    Glyph *child(int index) override;
    Glyph *parent() override;

private:
};

class Color;
class LinuxColor : public Color {
public:
    LinuxColor(unsigned char a, unsigned char b, unsigned char c, unsigned char d)
        : a(a),
          b(b),
          c(c),
          d(d) 
    {

    }

    LinuxColor(const SDL_Color &c)
        : a(c.r),
          b(c.b),
          c(c.g),
          d(c.a) 
    {

    }

    unsigned char R() const override { return a; }
    unsigned char G() const override { return b; }
    unsigned char B() const override { return c; }
    unsigned char D() const override { return d; }

    SDL_Color cast_sdl() { return {a, b, c, d}; }
private:
    unsigned char a, b, c, d;
};

#endif // LINUXORIGINAL_H
