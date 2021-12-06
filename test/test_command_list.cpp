#include "Commands.h"
#include <iostream>
#include <ostream>
#include <thread>
#include <unistd.h>

class AddCommand : public Command {
public:
    AddCommand()
        : Command("add command")
    {

    }

    void exec() override {
        std::cout << "1 + 1 = 2" << std::endl;
    }
};

int main() {
    CommandQueue *cq = new CommandQueue(2);
    auto run1 = [&]() {
        for (int i = 0; i < 1000; ++i)
            cq->put(new AddCommand());
    };

    auto run2 = [&]() {
        Command *c;
        for (;;) {
            c = cq->take();
            c->exec();
            delete c;
        }
    };

    std::thread t1(run1), t2(run2);
    sleep(1);

    t1.join();
    t2.join();
    delete cq;
}