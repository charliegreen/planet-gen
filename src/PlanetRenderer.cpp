#include <GL/glut.h>

#include "PlanetRenderer.hpp"
#include "ROAM.hpp"

static float viewAngle = 0;

PlanetRenderer::PlanetRenderer(Planet*p):
    NavigableRenderer(0,0,3*p->getRadius(),0,0,0),
    _planet(p)
{
    // ================================================================ set up basic ROAM cube
    _triangles = new std::list<ROAMTriangle*>();

    float r = _planet->getRadius()/2;
    glm::vec3 verts[] = {
	glm::vec3( r, r, r), glm::vec3( r, r,-r),
	glm::vec3( r,-r, r), glm::vec3( r,-r,-r),
	glm::vec3(-r, r, r), glm::vec3(-r, r,-r),
	glm::vec3(-r,-r, r), glm::vec3(-r,-r,-r)
    };

    // This makes significantly more sense if you draw a picture.
    
    // top/bot
    ROAMTriangle*t204 = new ROAMTriangle(verts[2], verts[0], verts[4]);
    ROAMTriangle*t462 = new ROAMTriangle(verts[4], verts[6], verts[2]);
    ROAMTriangle*t513 = new ROAMTriangle(verts[5], verts[1], verts[3]);
    ROAMTriangle*t375 = new ROAMTriangle(verts[3], verts[7], verts[5]);

    // front/back
    ROAMTriangle*t310 = new ROAMTriangle(verts[3], verts[1], verts[0]);
    ROAMTriangle*t023 = new ROAMTriangle(verts[0], verts[2], verts[3]);
    ROAMTriangle*t576 = new ROAMTriangle(verts[5], verts[7], verts[6]);
    ROAMTriangle*t645 = new ROAMTriangle(verts[6], verts[4], verts[5]);

    // left/right
    ROAMTriangle*t015 = new ROAMTriangle(verts[0], verts[1], verts[5]);
    ROAMTriangle*t540 = new ROAMTriangle(verts[5], verts[4], verts[0]);
    ROAMTriangle*t673 = new ROAMTriangle(verts[6], verts[7], verts[3]);
    ROAMTriangle*t326 = new ROAMTriangle(verts[3], verts[2], verts[6]);

    t015->_edges[0] = t310; t310->_edges[1] = t015;
    t204->_edges[0] = t023; t023->_edges[0] = t204;
    t204->_edges[1] = t540; t540->_edges[1] = t204;
    t204->_edges[2] = t462; t462->_edges[2] = t204;
    t462->_edges[0] = t645; t645->_edges[0] = t462;
    t462->_edges[1] = t326; t326->_edges[1] = t462;
    t326->_edges[0] = t023; t023->_edges[1] = t326;
    t310->_edges[2] = t023; t023->_edges[2] = t310;
    t513->_edges[1] = t310; t310->_edges[0] = t513;
    t015->_edges[1] = t513; t513->_edges[0] = t015;
    t015->_edges[2] = t540; t540->_edges[2] = t015;
    t576->_edges[0] = t375; t375->_edges[1] = t576;
    t540->_edges[0] = t645; t645->_edges[1] = t540;
    t673->_edges[0] = t576; t576->_edges[1] = t673;
    t375->_edges[0] = t673; t673->_edges[1] = t375;
    t326->_edges[2] = t673; t673->_edges[2] = t326;
    t645->_edges[2] = t576; t576->_edges[2] = t645;
    t375->_edges[2] = t513; t513->_edges[2] = t375;
    
    _triangles->push_front(t204);
    _triangles->push_front(t462);
    _triangles->push_front(t513);
    _triangles->push_front(t375);

    _triangles->push_front(t310);
    _triangles->push_front(t023);
    _triangles->push_front(t576);
    _triangles->push_front(t645);

    _triangles->push_front(t015);
    _triangles->push_front(t540);
    _triangles->push_front(t673);
    _triangles->push_front(t326);

    t462->split(this);
}

void PlanetRenderer::setup() {
    // set up lighting
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    GLfloat light0_amb[] = { 0.4, 0.4, 0.4, 1 };
    GLfloat light0_dif[] = { 0.4, 0.4, 0.4, 1 };
    glLightfv(GL_LIGHT0, GL_AMBIENT, light0_amb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_dif);
    
    glEnable(GL_LIGHT1);
    GLfloat light1_dif[] = { 0.6, 0.6, 0.4, 1 };
    GLfloat light1_pos[] = { 100000, 0, 0, 0 };
    glLightfv(GL_LIGHT1, GL_DIFFUSE,  light1_dif);
    glLightfv(GL_LIGHT1, GL_POSITION, light1_pos);

    // set up other stuff
    // glEnable(GL_LINE_SMOOTH);
    // glEnable(GL_BLEND);
    // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //glEnable(GL_CULL_FACE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    glMatrixMode(GL_PROJECTION);
    //gluPerspective(50, 1, 1.9*_planet->getRadius(), 4.1*_planet->getRadius());
    gluPerspective(50, 1, 1000, 4*_planet->getRadius());
    
    //glMatrixMode(GL_MODELVIEW);
    //gluLookAt(0,0,3*_planet->getRadius(),0,0,0,0,1,0);
    NavigableRenderer::setup();
}

void PlanetRenderer::display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glClear(GL_COLOR_BUFFER_BIT);
    // GLfloat amb[] = { .4, .4, .4, 1 };
    // GLfloat dif[] = { 1, 1, 1, 1 };
    // glMaterialfv(GL_FRONT, GL_AMBIENT, amb);
    // glMaterialfv(GL_FRONT, GL_DIFFUSE, dif);
    
    glPushMatrix();
    doTransformations();

    glRotatef(viewAngle, 0, 1, 0);
    // glRotatef(90,1,0,0);
    // glutSolidSphere(_planet->getRadius(),50,50); // TODO actually render planet

    std::list<ROAMTriangle*>::iterator i;
    for (i = _triangles->begin(); i != _triangles->end(); i++) {
    	(*i)->draw();
    }
    
    glPopMatrix();

    glutSwapBuffers();
}

void PlanetRenderer::idle() {
    viewAngle += 0.02;
    glutPostRedisplay();
}
