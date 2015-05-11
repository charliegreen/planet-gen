#ifndef MAIN_HPP
#define MAIN_HPP

#include <stdlib.h>
#include <stddef.h>
#include <stdarg.h>
#include <time.h>

class Main {
    static Main*_instance;

    Main();

public:
    static Main*getInstance();

    void main();
};

#endif
