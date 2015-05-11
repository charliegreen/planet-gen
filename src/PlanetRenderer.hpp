#ifndef PLANETRENDERER_H
#define PLANETRENDERER_H

#include "NavigableRenderer.hpp"
#include "Planet.hpp"

class PlanetRenderer : public NavigableRenderer {
    Planet*_planet;
    
public:
    PlanetRenderer(Planet*p);
    void setup();
    void display();
    void idle();
};

#endif
