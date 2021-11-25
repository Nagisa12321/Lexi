#ifndef COMPOSITOR_H
#define COMPOSITOR_H
#include "Composition.h"

class Composition;
class Compositor {
    // set the compostition
    void set_composition(Composition *);
    // when to compose
    virtual void compose(); 
};

#endif // COMPOSITOR_H
