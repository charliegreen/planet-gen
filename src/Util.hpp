#ifndef UTIL_H
#define UTIL_H

#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>

#include <GL/glut.h>
#include <glm/glm.hpp>

class Util {
public:
    static glm::vec3 aToVec3(float array[]);
    static void vec3ToA(glm::vec3 v, float*array);
};

#endif
