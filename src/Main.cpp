#include "Main.hpp"

#include <GL/glut.h>

Main*Main::_instance = NULL;

GLfloat light0_ambient[] = {0.2, 0.2, 0.2, 1.0}; // light0 is grey
GLfloat light0_diffuse[] = {0.0, 0.0, 0.0, 1.0};
GLfloat light1_diffuse[] = {1.0, 0.0, 0.0, 1.0}; // light1 is red
GLfloat light1_position[] = {1.0, 1.0, 1.0, 0.0};
GLfloat light2_diffuse[] = {0.0, 1.0, 0.0, 1.0}; // light2 is green
GLfloat light2_position[] = {-1.0, -1.0, 1.0, 0.0};
float s = 0;
GLfloat angle1 = 0;
GLfloat angle2 = 0;

Main::Main() {
    _instance = this;
}

Main*Main::getInstance(){
    return _instance ? _instance : _instance=new Main();
}

void Main::setup() {
    srand(time(NULL));

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
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_LINE_SMOOTH);
    glLineWidth(2.0);

    glMatrixMode(GL_PROJECTION);
    gluPerspective( /* field of view in degree */ 40.0,
		    /* aspect ratio */ 1.0,
		    /* Z near */ 1.0, /* Z far */ 10.0);
    glMatrixMode(GL_MODELVIEW);
    gluLookAt(0.0, 0.0, 5.0,  /* eye is at (0,0,5) */
	      0.0, 0.0, 0.0,      /* center is at (0,0,0) */
	      0.0, 1.0, 0.);      /* up is in positive Y direction */
    glTranslatef(0.0, 0.6, -1.0);
}

void Main::display(void) {
    static GLfloat amb[] = {0.4, 0.4, 0.4, 0.0};
    static GLfloat dif[] = {1.0, 1.0, 1.0, 0.0};

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_LIGHT1);
    glDisable(GL_LIGHT2);
    amb[3] = dif[3] = cos(s) / 2.0 + 0.5 + .2;
    glMaterialfv(GL_FRONT, GL_AMBIENT, amb);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, dif);

    glPushMatrix();
    glTranslatef(-0.3, -0.3, 0.0);
    glRotatef(angle1, 1.0, 5.0, 0.0);
    glCallList(1);		// render icosahedron
    glPopMatrix();

    glClear(GL_DEPTH_BUFFER_BIT);
    glEnable(GL_LIGHT2);
    glDisable(GL_LIGHT1);
    amb[3] = dif[3] = 0.5 - cos(s * .95) / 2.0 + .2;
    glMaterialfv(GL_FRONT, GL_AMBIENT, amb);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, dif);

    glPushMatrix();
    glTranslatef(0.3, 0.3, 0.0);
    glRotatef(angle2, 1.0, 0.0, 5.0);
    glCallList(1);		// render icosahedron
    glPopMatrix();

    // glPushAttrib(GL_ENABLE_BIT);
    // glDisable(GL_DEPTH_TEST);
    // glDisable(GL_LIGHTING);
    // glMatrixMode(GL_PROJECTION);
    // glPushMatrix();
    // glLoadIdentity();
    // gluOrtho2D(0, 1500, 0, 1500);
    // glMatrixMode(GL_MODELVIEW);
    // glPushMatrix();
    
    // glLoadIdentity();
    // /* Rotate text slightly to help show jaggies. */
    // glRotatef(4, 0.0, 0.0, 1.0);
    // //output(200, 225, "This is antialiased.");
    // glDisable(GL_LINE_SMOOTH);
    // glDisable(GL_BLEND);
    // //output(160, 100, "This text is not.");
    // glPopMatrix();
    // glMatrixMode(GL_PROJECTION);
    // glPopMatrix();
    // glPopAttrib();
    // glMatrixMode(GL_MODELVIEW);

    glutSwapBuffers();
}

void display(void) {
    Main::getInstance()->display();
}

void idle(void) {
    angle1 = (GLfloat) fmod(angle1 + 0.8, 360.0);
    angle2 = (GLfloat) fmod(angle2 + 1.1, 360.0);
    s += 0.05;
    glutPostRedisplay();
}

int main(int argc, char*argv[]){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800,800);
    glutCreateWindow(NAME);
    
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    
    Main::getInstance()->setup();    
    glutMainLoop();
    return 0;
}
