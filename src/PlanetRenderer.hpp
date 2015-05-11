#ifndef PLANETRENDERER_H
#define PLANETRENDERER_H

#include <list>

#include "NavigableRenderer.hpp"
#include "Planet.hpp"

#include "ROAM.hpp"

class PlanetRenderer : public NavigableRenderer {
    Planet*_planet;
    std::list<ROAMTriangle*>*_triangles;
    
public:
    PlanetRenderer(Planet*p);
    void setup();
    void display();
    void idle();
};

#endif
