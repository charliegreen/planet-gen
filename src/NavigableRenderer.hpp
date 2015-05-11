#ifndef NAVIGABLERENDERER_H
#define NAVIGABLERENDERER_H

#include "Renderer.hpp"

class NavigableRenderer : public Renderer {
    float _x, _y, _z;
    float _th1, _th2, _th3;
    float _dx, _dy, _dz;
    //float _zfar, _znear;
    
protected:
    void doTransformations();
    
public:
    NavigableRenderer(float x, float y, float z, float th1, float th2, float th3);
    void setup();
    void mouseClick(int button, int state, int x, int y);
    void mouseMotion(int x, int y);
    void keyboard(unsigned char key, int x, int y);
};

#endif
