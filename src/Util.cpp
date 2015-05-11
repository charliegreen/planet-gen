#include "Util.hpp"

glm::vec3 Util::aToVec3(float array[]) {
    return glm::vec3(array[0], array[1], array[2]);
}

void Util::vec3ToA(glm::vec3 v, float*array) {
    array[0] = v.x;
    array[1] = v.y;
    array[2] = v.z;
}
