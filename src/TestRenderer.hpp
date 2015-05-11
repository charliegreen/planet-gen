#ifndef TESTRENDERER_H
#define TESTRENDERER_H

#include "Renderer.hpp"

class TestRenderer : public Renderer {
public:
    void setup();
    void display();
    void idle();
};

#endif
