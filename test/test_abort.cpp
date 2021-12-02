#include "Utils.h"

int main() {
    lexi_abort("test abort\n");
    int *pi = new int(100);
    delete pi;
    *pi = 100;
}