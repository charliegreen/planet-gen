#include <GL/freeglut.h>
#include <string.h>
#include <unistd.h>

#include "PlanetRenderer.hpp"
#include "ROAM.hpp"

// comment to suppress updateROAM's metadata output
#define UPDATEROAM_PRINTINFO

static float viewAngle = 0;

PlanetRenderer::PlanetRenderer(Planet*p):
    NavigableRenderer(glm::vec3(0,0,3*p->getRadius()),
		      glm::vec3(0,0,-1),
		      glm::vec3(0,1,0)),
    _planet(p)
{
    _triangles = new std::list<ROAMTriangle*>();
    _diamonds  = new std::list<ROAMDiamond*>();

    // ================================================================ set up basic ROAM cube
    float r = _planet->getRadius()/sqrt(3);
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

    std::list<ROAMTriangle*>::iterator i;
    for (i = _triangles->begin(); i != _triangles->end(); i++) {
    	ROAMTriangle*t = *i;
	t->updateError(_planet);
    }
    
    /* I'm keeping the code for setting up the grid in case I need it, but I probably won't,
       and you probably shouldn't uncomment this and expect other things to still work. If
       you do uncomment it, comment the above code that creates the initial ROAM cube.
#define GRIDSIZE 3
#define GRIDWIDTH 4500
    
    ROAMTriangle*grid[GRIDSIZE][GRIDSIZE][2];
    for (int i = 0; i < GRIDSIZE; i++) {
	for (int j = 0; j < GRIDSIZE; j++) {
	    int x1 = i*GRIDWIDTH-GRIDSIZE*GRIDWIDTH/2;
	    int y1 = j*GRIDWIDTH-GRIDSIZE*GRIDWIDTH/2;
	    int x2 = x1 + GRIDWIDTH;
	    int y2 = y1 + GRIDWIDTH;
	    glm::vec3 xy = glm::vec3(x1,y1,0);
	    glm::vec3 xY = glm::vec3(x1,y2,0);
	    glm::vec3 Xy = glm::vec3(x2,y1,0);
	    glm::vec3 XY = glm::vec3(x2,y2,0);
	    
	    grid[i][j][0] = new ROAMTriangle(Xy,xy,xY);
	    grid[i][j][1] = new ROAMTriangle(xY,XY,Xy);	
	    grid[i][j][0]->_edges[0] = NULL;
	    grid[i][j][0]->_edges[1] = NULL;
	    grid[i][j][0]->_edges[2] = grid[i][j][1];
	    grid[i][j][1]->_edges[0] = NULL;
	    grid[i][j][1]->_edges[1] = NULL;
	    grid[i][j][1]->_edges[2] = grid[i][j][0];

	    _triangles->push_front(grid[i][j][0]); // we still have grid to modify edge pointers
	    _triangles->push_front(grid[i][j][1]);
	}
    }

    for (int i = 0; i < GRIDSIZE; i++) {
	for (int j = 0; j < GRIDSIZE; j++) {
	    grid[i][j][0]->_edges[0] = j>0 ? grid[i][j-1][1] : NULL;
	    grid[i][j][0]->_edges[1] = i>0 ? grid[i-1][j][1] : NULL;
	    grid[i][j][1]->_edges[0] = j<GRIDSIZE-1 ? grid[i][j+1][0] : NULL;
	    grid[i][j][1]->_edges[1] = i<GRIDSIZE-1 ? grid[i+1][j][0] : NULL;
	}
    }    
    */
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

#if PLANETRENDERER_WIREFRAME
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
#else
    glEnable(GL_CULL_FACE);
    
    glEnable(GL_STENCIL_TEST);
    glStencilFunc(GL_ALWAYS, 3, 0xffffffff);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
#endif
    
    glMatrixMode(GL_PROJECTION);
    //gluPerspective(50, 1, 1.9*_planet->getRadius(), 4.1*_planet->getRadius());
    gluPerspective(50, 1, 1000, 4*_planet->getRadius());
}

void PlanetRenderer::display() {
    unsigned long long start = Util::timeMillis();
    static int fps = 0;
    static int lastFps = 60;
    static unsigned long long last = start;

    // ---------------- rendering setup
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glClear(GL_COLOR_BUFFER_BIT);
    // GLfloat amb[] = { .4, .4, .4, 1 };
    // GLfloat dif[] = { 1, 1, 1, 1 };
    // glMaterialfv(GL_FRONT, GL_AMBIENT, amb);
    // glMaterialfv(GL_FRONT, GL_DIFFUSE, dif);
    
    glPushMatrix();
    doTransformations();
    glRotatef(viewAngle, 0, 1, 0);

    // ---------------- actually draw the planet
    std::list<ROAMTriangle*>::iterator i;
    for (i = _triangles->begin(); i != _triangles->end(); i++) {
    	(*i)->draw();
    }
    
    // ---------------- draw text on screen
    glPushAttrib(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);
    glLoadIdentity();
    
    char text[24];
    memset(text,0,sizeof(text));

    glWindowPos2i(10, 780);
    snprintf(text,sizeof(text),"%lu triangles", _triangles->size());
    glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)text);

    glWindowPos2i(10, 760);
    snprintf(text,sizeof(text),"%lu diamonds", _diamonds->size());
    glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)text);

    glWindowPos2i(10, 740);
    snprintf(text,sizeof(text),"%d fps",lastFps);
    glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)text);

    glPopAttrib();
    glPopMatrix();

    if (last < Util::timeMillis()-1000) {
	last = Util::timeMillis();
	lastFps = fps;
	fps = 0;
    } else {
	fps++;
    }
    
    glutSwapBuffers();
}

void PlanetRenderer::keyboard(unsigned char key, int x, int y){
    NavigableRenderer::keyboard(key,x,y);

    switch(key) {
    case ' ':{
	std::cout << "Split? ";
	int split;
	std::cin >> split;
	if (split < 0)
	    return;
	
	std::list<ROAMTriangle*>::iterator i;
	std::list<ROAMTriangle*>::iterator end = _triangles->end();
	for (i = _triangles->begin(); i != end; i++) {
	    ROAMTriangle*t = *i;
	    if (t->_id == split) {
		t->split(this);
	    }
	}
    }break;

    case '.':{
	updateROAM();
    }break;
    }
}

void PlanetRenderer::updateROAM() {
#ifdef UPDATEROAM_PRINTINFO
    std::cout << "Updating ROAM...";
    std::cout.flush();
    unsigned long long start = Util::timeMillis();

    int nT = _triangles->size();
    int nD = _diamonds->size();
#endif
    int numSplits = 0;
    int numMerges = 0;
    
    // current camera location
    glm::vec3 pos = getPosition();
    glm::vec3 dir = getDirection();

    // ================================ update mesh
    //std::list<ROAMTriangle*> triangles = std::list<ROAMTriangle*>(*_triangles);
    
    static const float splitPriority = .0001;//1000;

    // do merging first so we don't go through diamonds we just made
    //std::cout << "Testing " << _diamonds->size() << " diamonds.\n";
    std::list<ROAMDiamond*>::iterator j;
    std::list<ROAMDiamond*>::iterator jend = _diamonds->end();
    for(j = _diamonds->begin(); j != jend;) {
	ROAMDiamond*d = *j;
	j++; // increment here so modifications to d don't invalidate our iterator

	//std::cout << "Testing diamond " << d << "\n";
	if (d->getMergePriority(pos,dir) < splitPriority) {
	    d->merge(this);
	    numMerges++;
	}
    }

    std::list<ROAMTriangle*>::iterator i;
    std::list<ROAMTriangle*>::iterator iend = _triangles->end();
    for (i = _triangles->begin(); i != iend; i++) {
    	ROAMTriangle*t = *i;	

	if (t->getSplitPriority(pos,dir) > splitPriority) {
    	    numSplits += t->split(this);
    	}
    }

#ifdef UPDATEROAM_PRINTINFO
    std::cout << "Done. [" << (Util::timeMillis()-start) << "ms]\n";
    std::cout << "    splits         : " << numSplits << "\n";
    std::cout << "    merges         : " << numMerges << "\n";
    std::cout << "    total triangles: " << _triangles->size() << "\n";
    std::cout << "    new triangles  : " << (_triangles->size()-nT) << "\n";
    std::cout << "    new diamonds   : " << (_diamonds->size() -nD) << "\n";
    // printf("Done. (%d splits, %lu total triangles, %d new triangles, %d new diamonds) [%llums]\n",
    // 	   numSplits, _triangles->size(),
    // 	   (int)(_triangles->size()-nT), (int)(_diamonds->size()-nD),
    // 	   Util::timeMillis()-start);
#endif
}

void PlanetRenderer::idle() {
#if PLANETRENDERER_ROTATE
    viewAngle += 0.2;
#endif

    //updateROAM();
    
    glutPostRedisplay();
}
