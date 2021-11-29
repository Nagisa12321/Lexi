#include <iostream>

using namespace std;

class A {
public:
    virtual void show() const { cout << "A!" << endl; }
};

class B : public A {
public:
    virtual void show() const { cout << "B!" << endl; }
};

void show(const A &a) { a.show(); }

int main() {
    show(B()); 
}