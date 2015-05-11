#include "NavigableRenderer.hpp"

#include <GL/glut.h>
#include <stdio.h>

NavigableRenderer::NavigableRenderer(float x, float y, float z, float th1, float th2, float th3):
    _x(x), _y(y), _z(z), _th1(th1), _th2(th2), _th3(th3)
{
    _dx = 0;
    _dy = 0;
    _dz = 0;
    // _znear = 12000;
    // _zfar = 24000;
}

void NavigableRenderer::doTransformations() {
    //gluPerspective(70,1,_znear,_zfar);
    glRotatef(_th1, 1, 0, 0);
    glRotatef(_th2, 0, 1, 0);
    glRotatef(_th3, 0, 0, 1);
    glTranslatef(_dx,_dy,_dz);
    //glTranslatef(-_x,-_y,-_z);
    //glMatrixMode(GL_MODELVIEW);
    //gluLookAt(_x,_y,_z,0,0,0,0,1,0);
}

void NavigableRenderer::setup() {
    glMatrixMode(GL_MODELVIEW);
    gluLookAt(_x,_y,_z,0,0,0,0,1,0);
}

void NavigableRenderer::mouseClick(int button, int state, int x, int y){
    // TODO?
}

void NavigableRenderer::mouseMotion(int x, int y){
    // TODO?
}

void NavigableRenderer::keyboard(unsigned char key, int x, int y){
    static const float dtheta = 1;
    static const float dx = 100;
    // static const float dplane = 100;

    switch(key){
    case 'w':	_th1 += dtheta; break;
    case 's':	_th1 -= dtheta; break;

    case 'a':	_th3 += dtheta; break;
    case 'd':	_th3 -= dtheta; break;

    case 'q':	_th2 += dtheta; break;
    case 'e':	_th2 -= dtheta; break;
 
    case 'j':	_dx += dx; break;
    case 'l':	_dx -= dx; break;

    case 'h':	_dy += dx; break;
    case 'n':	_dy -= dx; break;

    case 'i':	_dz += dx; break;
    case 'k':	_dz -= dx; break;

    // case 'r':	_znear += dplane; break;
    // case 'f':	_znear -= dplane; break;

    // case 't':	_zfar += dplane; break;
    // case 'g':	_zfar -= dplane; break;
	
    default: break;
    }

    // printf("znear %f, zfar %f\n", _znear, _zfar);
}
