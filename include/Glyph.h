#ifndef GLYPH_H
#define GLYPH_H
#include <list>
#include "Types.h"
#include "Events.h"

class WindowRect;
class Point;
class Window;    
class Glyph {
public: 
    Glyph(const WindowRect &rect);
    Glyph(const Glyph &) = delete;
    virtual ~Glyph() = 0;
    
    Glyph &operator=(const Glyph &) = delete;

    /* Performance */
    // how to draw myself?
    virtual void draw(Window *w) = 0;
    // how much space do i take up
    void bounds(WindowRect &r);

    /* Click to detect */
    virtual bool intersects(const Point &p);

    /* struct */
    // insert a child in index 
    virtual void insert(Glyph *child, int index) = 0;
    virtual void add(Glyph *child) = 0;
    // remove a children 
    virtual void remove(Glyph *child) = 0;
    // get a child with index
    virtual Glyph *child(int index) = 0;
    // get my parent
    virtual Glyph *parent() = 0;

    virtual void process_event(const Event &event) = 0;
protected:
    WindowRect m_rect;
};

class Composition : public Glyph {
public:
    Composition(const WindowRect &rect, Glyph *parent);
    virtual ~Composition();
    /* the copy operatorion is defaultly deleted */

    // delete the copy operation;
    Composition(const Composition &) = delete;
    Composition &operator=(const Composition &) = delete;

    void draw(Window *w) override;
    void insert(Glyph *child, int index) override;
    void add(Glyph *child) override;
    void remove(Glyph *child) override;
    void process_event(const Event &event) override;

    Glyph *child(int index) override;
    Glyph *parent() override;

protected:
    std::list<Glyph *>  m_components;
    // TODO: safety delete the parent member;
    Glyph               *m_parent;
};

#endif // GLYPH_H
