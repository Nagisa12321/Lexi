#ifndef UTILS_H
#define UTILS_H
#include <iostream>

template <typename _Iterator>
void container_printer(_Iterator first, _Iterator end, std::ostream &out = std::cout) {
    out << "[";
    while (first != end) out << *first++ << ", ";
    out << "]" << std::endl;
}

void lexi_abort(const char *info);

#endif // UTILS_H
