#ifndef PLANETRENDERER_H
#define PLANETRENDERER_H

#include "Renderer.hpp"
#include "Planet.hpp"

class PlanetRenderer : public Renderer {
    Planet*_planet;
    
public:
    PlanetRenderer(Planet*p);
    void setup();
    void display();
    void idle();
};

#endif
