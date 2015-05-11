#ifndef MAIN_HPP
#define MAIN_HPP

#include <stdlib.h>
#include <stddef.h>
#include <stdarg.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#define NAME "planet-gen"

class Main {
    static Main*_instance;

    Main();

public:
    static Main*getInstance();

    void setup();
    void display();
};

#endif
