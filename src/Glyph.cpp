#include "Glyph.h"
using namespace std;
////////////////
// Glyph impl //
////////////////
Glyph::Glyph(const WindowRect &rect) 
    : m_rect(rect) {}

Glyph::~Glyph() {}

void Glyph::bounds(WindowRect &r) { r = m_rect; }

bool Glyph::intersects(const Point &p) {
    return p.x >= m_rect.x && 
           p.y >= m_rect.y && 
           (p.x - m_rect.x) < m_rect.width && 
           (p.y - m_rect.y) < m_rect.height;
}


//////////////////////
// Composition impl //
//////////////////////
Composition::Composition(const WindowRect &rect, Glyph *parent)
    : Glyph(rect),
      m_components(),
      m_parent(parent) {}

Composition::~Composition() {}

void Composition::draw(Window *w) {
    for (Glyph *g : m_components)
        g->draw(w);
}

void Composition::insert(Glyph *child, int index) {
    auto iter = m_components.begin();
    for (int i = 0; i < index; ++i)
        ++iter;
    m_components.insert(iter, child);
}

void Composition::add(Glyph *child) {
    m_components.push_back(child);
}

void Composition::remove(Glyph *child) {
    m_components.remove(child);
}

Glyph *Composition::child(int index) {
    auto iter = m_components.begin();
    for (int i = 0; i < index; ++i)
        ++iter;
    return *iter;
}

Glyph *Composition::parent() {
    return m_parent;
}
