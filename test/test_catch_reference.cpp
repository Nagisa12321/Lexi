#include <iostream>
#include <thread>
using namespace std;

class A {};

thread t;

void start(A *pa) {
    cout << pa << endl;
    auto run = [&] {
        cout << pa << endl;
    };

    thread _t(run);
    t.swap(_t);
}

void end() { t.join(); }

int main() {
    A *pi = new A;
    start(pi);
    end();
}