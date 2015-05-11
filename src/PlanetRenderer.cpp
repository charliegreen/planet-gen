#include <GL/glut.h>

#include "PlanetRenderer.hpp"
#include <stdio.h>

static float viewAngle = 0;

PlanetRenderer::PlanetRenderer(Planet*p):
    NavigableRenderer(0,0,3*p->getRadius(),90,0,0), _planet(p)
{}

void PlanetRenderer::setup() {
    // set up lighting
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    GLfloat light0_amb[] = { 0.4, 0.4, 0.4, 1 };
    GLfloat light0_dif[] = { 0.4, 0.4, 0.4, 1 };
    glLightfv(GL_LIGHT0, GL_AMBIENT, light0_amb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_dif);

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
    glRotatef(-viewAngle, 0, 0, 1);
    glutSolidSphere(_planet->getRadius(),50,50); // TODO actually render planet
    glPopMatrix();

    glutSwapBuffers();
}

void PlanetRenderer::idle() {
    viewAngle += 0.02;
    glutPostRedisplay();
}
