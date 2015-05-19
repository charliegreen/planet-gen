#ifndef PLANETRENDERER_H
#define PLANETRENDERER_H

#include <list>

#include "NavigableRenderer.hpp"
#include "Planet.hpp"

#include "ROAM.hpp"

// set to 0 to keep from slowly rotating planets
#define PLANETRENDERER_ROTATE 1

// set to 1 to enable wireframe drawing
#define PLANETRENDERER_WIREFRAME 0

class PlanetRenderer : public NavigableRenderer {
    friend class ROAMTriangle;
    friend class ROAMDiamond;

    Planet*_planet;
    std::list<ROAMTriangle*>*_triangles;
    std::list<ROAMDiamond*>* _diamonds;

    void updateROAM();
    
public:
    PlanetRenderer(Planet*p);
    void setup();
    void display();
    void idle();
    void keyboard(unsigned char key, int x, int y);
};

// see comment at top of Main.cpp
extern PFNGLWINDOWPOS2IPROC glWindowPos2i;

#endif
