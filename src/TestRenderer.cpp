#include <GL/glut.h>
#include <math.h>

#include "TestRenderer.hpp"

GLfloat light0_ambient[] = {0.2, 0.2, 0.2, 1.0}; // light0 is grey
GLfloat light0_diffuse[] = {0.0, 0.0, 0.0, 1.0};
GLfloat light1_diffuse[] = {1.0, 0.0, 0.0, 1.0}; // light1 is red
GLfloat light1_position[] = {1.0, 1.0, 1.0, 0.0};
GLfloat light2_diffuse[] = {0.0, 1.0, 0.0, 1.0}; // light2 is green
GLfloat light2_position[] = {-1.0, -1.0, 1.0, 0.0};
float s = 0;
GLfloat angle1 = 0;
GLfloat angle2 = 0;

void TestRenderer::setup() {
    // create an icosahedron and bind it to list 1
    glNewList(1, GL_COMPILE);
    glutSolidIcosahedron();
    glEndList();

    // set up lighting
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
    glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, light2_diffuse);
    glLightfv(GL_LIGHT2, GL_POSITION, light2_position);

    // set up other stuff
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_LINE_SMOOTH);
    
    glMatrixMode(GL_PROJECTION);
    gluPerspective(70.0, 	// field of view in degrees
		   1.0,		// aspect ratio
		   1.0,		// Z near
		   10.0);	// Z far
    glMatrixMode(GL_MODELVIEW);
    gluLookAt(0.0, 0.0, 8,	// eye is at (0, 0, 8)
	      0.0, 0.0, 0.0,	// center at (0, 0, 0)
	      0.0, 1.0, 0.);	// up is positive Y
    glTranslatef(0.0, 0.6, -1.0);

    // wireframe mode
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // GL_FILL to turn off wireframe
}

void TestRenderer::display(void) {
    static GLfloat amb[] = {0.4, 0.4, 0.4, 0.0};
    static GLfloat dif[] = {1.0, 1.0, 1.0, 0.0};

    // render red icosahedron
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_LIGHT1);
    glDisable(GL_LIGHT2);
    amb[3] = dif[3] = cos(s) / 2.0 + 0.5 + .2;
    glMaterialfv(GL_FRONT, GL_AMBIENT, amb);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, dif);

    glPushMatrix();
    glTranslatef(-4, 0.0, 0.0);
    glRotatef(angle1, 1.0, 0.0, 0.0);
    glCallList(1);		// render icosahedron
    glPopMatrix();

    // render green icosahedron
    glClear(GL_DEPTH_BUFFER_BIT);
    glEnable(GL_LIGHT2);
    glDisable(GL_LIGHT1);
    amb[3] = dif[3] = 0.5 - cos(s * .95) / 2.0 + .2;
    glMaterialfv(GL_FRONT, GL_AMBIENT, amb);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, dif);

    glPushMatrix();
    glTranslatef(4, 0.0, 0.0);
    glRotatef(angle2, 0.0, 1.0, 0.0);
    glCallList(1);		// render icosahedron
    glPopMatrix();

    // render a teapot
    glClear(GL_DEPTH_BUFFER_BIT);
    glEnable(GL_LIGHT1);
    amb[3] = dif[3] = .7;
    glMaterialfv(GL_FRONT, GL_AMBIENT, amb);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, dif);
    glPushMatrix();
    glRotatef(angle1, 1, 1, 1);
    //glutSolidSphere(1,16,16);
    glutSolidTeapot(1);
    glPopMatrix();
    
    glutSwapBuffers();
}

void TestRenderer::idle(void) {
    angle1 = (GLfloat) fmod(angle1 + 0.8, 360.0);
    angle2 = (GLfloat) fmod(angle2 + 1.1, 360.0);
    s += 0.05;
    glutPostRedisplay();
}
