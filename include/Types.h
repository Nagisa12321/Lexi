#ifndef TYPES_H
#define TYPES_H

enum FontSize { max, mid, min };

struct WindowRect {
    int x, y;
    int width, height;
};

struct Point {
    int x, y;
};

struct Color {
    virtual ~Color() = default;
    virtual unsigned char R() const = 0;
    virtual unsigned char G() const = 0;
    virtual unsigned char B() const = 0;
    virtual unsigned char D() const = 0;
};

#endif // TYPES_H
