#include <GL/glut.h>
#include <time.h>

#include "Main.hpp"
#include "TestRenderer.hpp"
#include "PlanetRenderer.hpp"

#include <GL/freeglut_ext.h>
// We have to import this because it's technically an OpenGL extension or something? See:
// https://stackoverflow.com/questions/18821558/function-glwindowpos2i-could-not-be-resolved
PFNGLWINDOWPOS2IPROC glWindowPos2i;

Main*Main::_instance = NULL;
Renderer*Main::_renderer = NULL;

Main::Main() {
    _instance = this;
}

Main*Main::getInstance(){
    return _instance ? _instance : _instance=new Main();
}

void Main::setRenderer(Renderer*r) {
    _renderer = r;
    if (r)
	r->setup();
}

Renderer*Main::getRenderer() {
    return _renderer;
}

void display(void) {	Main::getInstance()->getRenderer()->display();	}
void idle(void)	   {	Main::getInstance()->getRenderer()->idle();	}

void mouseClick(int button, int state, int x, int y) {
    Main::getInstance()->getRenderer()->mouseClick(button, state, x, y);
}

void mouseMotion(int x, int y) {
    Main::getInstance()->getRenderer()->mouseMotion(x, y);
}

void keyboard(unsigned char key, int x, int y){
    Main::getInstance()->getRenderer()->keyboard(key, x, y);
}

int main(int argc, char*argv[]){
    glutInit(&argc, argv);
    // see comment at top of file, by definition of glWindowPos2i
    glWindowPos2i = (PFNGLWINDOWPOS2IPROC) glutGetProcAddress("glWindowPos2i");
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800,800);
    glutCreateWindow(NAME);

    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouseClick);
    glutMotionFunc(mouseMotion);

    srand(time(NULL));

    //Renderer*r = new TestRenderer();
    Main::getInstance()->setRenderer(new PlanetRenderer(new Planet(6000)));
    glutMainLoop();
    return 0;
}
