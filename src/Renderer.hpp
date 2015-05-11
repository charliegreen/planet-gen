#ifndef RENDERER_H
#define RENDERER_H

class Renderer {
public:
    virtual void setup(void){}
    virtual void display(void){}
    virtual void idle(void){}
};

#endif
