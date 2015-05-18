#ifndef PLANETRENDERER_H
#define PLANETRENDERER_H

#include <list>

#include "NavigableRenderer.hpp"
#include "Planet.hpp"

#include "ROAM.hpp"

// comment to keep from slowly rotating planets
//#define PLANETRENDERER_ROTATE

class PlanetRenderer : public NavigableRenderer {
    friend class ROAMTriangle;
    friend class ROAMDiamond;

    Planet*_planet;
    std::list<ROAMTriangle*>*_triangles;

    void updateROAM();
    
public:
    PlanetRenderer(Planet*p);
    void setup();
    void display();
    void idle();
    void keyboard(unsigned char key, int x, int y);
};

#endif
