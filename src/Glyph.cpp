#include "Glyph.h"
using namespace std;
////////////////
// Glyph impl //
////////////////
Glyph::Glyph(const WindowRect &rect) 
    : m_rect(rect) {}

void Glyph::bounds(WindowRect &r) { r = m_rect; }

//////////////////////
// Composition impl //
//////////////////////
Composition::Composition(const WindowRect &rect, Glyph *parent)
    : Glyph(rect),
      m_components(),
      m_parent(parent) {}

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
