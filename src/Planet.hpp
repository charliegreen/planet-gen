#ifndef PLANET_H
#define PLANET_H

class Planet {
    float _radius;		// baseline radius, in km

public:
    Planet(float radius);	// units are km

    float getRadius();
    float altitude(float theta, float phi); // gets rho in km for spherical coords rho/theta/phi
};

#endif
