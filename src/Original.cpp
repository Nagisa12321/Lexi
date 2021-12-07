#include "Original.h"
#include "Types.h"
#include <fstream>
#include <string>
using namespace std;

std::string to_string(const Point &point) {
	std::string res;
	res += "[";
	res += to_string(point.x);
	res += ", ";
	res += to_string(point.y);
	res += "]";
	return res;
}

std::string to_string(const WindowRect &rect) {
	std::string res;
	res += ("[");
	res += to_string(rect.x);
	res += ", ";
	res += to_string(rect.y);
	res += ", ";
	res += to_string(rect.width);
	res += ", ";
	res += to_string(rect.height);
	res += ("]");
	return res;
}

static void __fn() {}
Button::Button(const WindowRect &rect, const std::string &name)
    : Glyph(rect),
      m_press_handler(__fn),
      m_release_handler(__fn),
      m_name(name),
      m_pressed(false)
{
    
}

void Button::add_press_handler(const std::function<void()> &fn) { m_press_handler = fn; }
void Button::add_release_handler(const std::function<void()> &fn) { m_release_handler = fn; }
