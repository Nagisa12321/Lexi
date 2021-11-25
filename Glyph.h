#ifndef GLYPH_H
#define GLYPH_H

class Window;
class Rect;
class Point;
class Glyph {
    /* Performance */
    // how to draw myself?
    virtual void draw(Window *w) = 0;
    // how much space do i take up
    virtual void bounds(Rect &r) = 0;

    /* Click to detect */
    virtual bool intersects(const Point &p) = 0;

    /* struct */
    // insert a child in index 
    virtual void insert(Glyph *child, int index) = 0;
    // remove a children 
    virtual void remove(Glyph *child) = 0;
    // get a child with index
    virtual Glyph *child(int index) = 0;
    // get my parent
    virtual Glyph *parent() = 0;
};

#endif // GLYPH_H
