#ifndef PLANET_H
#define PLANET_H

#include <glm/glm.hpp>

class Planet {
    float _radius;		// baseline radius, in km

public:
    Planet(float radius);	// units are km

    float getRadius();
    float altitude(float theta, float phi); // gets rho in km for spherical coords rho/theta/phi
    float altitude(glm::vec3 unitvec); // gets rho in km in direction of unitvec
};

#endif
