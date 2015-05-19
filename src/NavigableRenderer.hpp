#ifndef NAVIGABLERENDERER_H
#define NAVIGABLERENDERER_H

#include <glm/glm.hpp>

#include "Renderer.hpp"

class NavigableRenderer : public Renderer {
    glm::vec3 _pos;
    glm::vec3 _dir;
    glm::vec3 _up;
    
protected:
    void doTransformations();
    
public:
    NavigableRenderer(glm::vec3 pos, glm::vec3 dir, glm::vec3 up);
    void mouseClick(int button, int state, int x, int y);
    void mouseMotion(int x, int y);
    void keyboard(unsigned char key, int x, int y);
};

#endif
