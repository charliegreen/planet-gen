#ifndef MAIN_HPP
#define MAIN_HPP

#include <stdlib.h>
#include <stddef.h>
#include <stdarg.h>

#define NAME "planet-gen"

#include "Renderer.hpp"

class Main {
    static Main*_instance;
    static Renderer*_renderer;
    Main();

public:
    static Main*getInstance();
    void setRenderer(Renderer*r);
    Renderer*getRenderer();
};

#endif
