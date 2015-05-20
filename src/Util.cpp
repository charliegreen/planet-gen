#include <sys/time.h>

#include "Util.hpp"

glm::vec3 Util::aToVec3(float array[]) {
    return glm::vec3(array[0], array[1], array[2]);
}

void Util::vec3ToA(glm::vec3 v, float*array) {
    array[0] = v.x;
    array[1] = v.y;
    array[2] = v.z;
}

unsigned long long Util::timeMillis() {
    struct timeval tp;
    gettimeofday(&tp, NULL);
    return tp.tv_sec*1000+tp.tv_usec/1000;
}

glm::vec3 Util::mulvec3(glm::vec3 v, float a) {
    return v*a;
}

std::ostream&operator<<(std::ostream&strm, const glm::vec3 v) {
    return strm << "<" << v.x << ", " << v.y << ", " << v.z << ">";
}
