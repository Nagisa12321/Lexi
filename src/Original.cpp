#include "Original.h"
using namespace std;

Button::Button(const WindowRect &rect, const std::string &name)
    : Glyph(rect),
      m_name(name)
{
    
}

