#include <iostream>
#include <list>
#include "Utils.h"

using namespace std;

int main() {
    list<int *> ili;
    int a = 0, b = 1, c = 2;
    ili.push_back(&a);
    ili.push_back(&b);
    ili.push_back(&c);
    container_printer(ili.begin(), ili.end());
    ili.remove(&b);
    container_printer(ili.begin(), ili.end());
}