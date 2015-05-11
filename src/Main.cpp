#include <GL/glut.h>
#include <time.h>

#include "Main.hpp"
#include "TestRenderer.hpp"

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

int main(int argc, char*argv[]){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800,800);
    glutCreateWindow(NAME);
    
    glutDisplayFunc(display);
    glutIdleFunc(idle);

    srand(time(NULL));

    //Renderer*r = new TestRenderer();
    Main::getInstance()->setRenderer(new TestRenderer());
    glutMainLoop();
    return 0;
}
