#ifndef RENDERER_H
#define RENDERER_H

class Renderer {
public:
    virtual void setup(){}
    virtual void display(){}
    virtual void idle(){}

    virtual void mouseClick(int button, int state, int x, int y){}
    virtual void mouseMotion(int x, int y){}
    virtual void keyboard(unsigned char key, int x, int y){}
};

#endif
