#include "Planet.hpp"

Planet::Planet(float radius):
    _radius(radius)
{}

float Planet::getRadius(){ return _radius; }

float Planet::altitude(float theta, float phi) {
    return _radius;
}

float Planet::altitude(glm::vec3 unitvec) {
    return _radius;
}
