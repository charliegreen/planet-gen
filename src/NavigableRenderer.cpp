#include "NavigableRenderer.hpp"

#include <GL/glut.h>
#include <glm/gtx/rotate_vector.hpp>
#include <stdio.h>
#include <math.h>

NavigableRenderer::NavigableRenderer(glm::vec3 pos, glm::vec3 dir, glm::vec3 up):
    _pos(pos)
{
    _dir = glm::normalize(dir);
    _up  = glm::normalize(up);
}

void NavigableRenderer::doTransformations() {
    gluLookAt(_pos.x, _pos.y, _pos.z,
	      _pos.x+_dir.x, _pos.y+_dir.y, _pos.z+_dir.z,
	      _up.x, _up.y, _up.z);
}

void NavigableRenderer::mouseClick(int button, int state, int x, int y){
    // TODO?
}

void NavigableRenderer::mouseMotion(int x, int y){
    // TODO?
}

void NavigableRenderer::keyboard(unsigned char key, int x, int y){
    static const float dtheta = M_PI/6;
    static const float dx = 100;
    
    switch(key){
    case 'w':	_dir = glm::rotate(_dir,  dtheta, glm::cross(_dir, _up)); break;
    case 's':	_dir = glm::rotate(_dir, -dtheta, glm::cross(_dir, _up)); break;

    case 'a':	_dir = glm::rotate(_dir,  dtheta, _up); break;
    case 'd':	_dir = glm::rotate(_dir, -dtheta, _up); break;

    case 'q':	_up = glm::rotate(_up, -dtheta, _dir); break;
    case 'e':	_up = glm::rotate(_up,  dtheta, _dir); break;
 
    case 'j':	_pos -= dx*glm::cross(_dir, _up); break;
    case 'l':	_pos += dx*glm::cross(_dir, _up); break;

    case 'h':	_pos += dx*_up; break;
    case 'n':	_pos -= dx*_up; break;

    case 'i':	_pos += dx*_dir; break;
    case 'k':	_pos -= dx*_dir; break;
	
    default: break;
    }
}
