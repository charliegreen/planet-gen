#include <GL/freeglut.h>
#include <stdlib.h>
#include <unistd.h>

#include "ROAM.hpp"
#include "PlanetRenderer.hpp"

//#define TRIANGLE_DRAW_IDS
//#define PRINT_SPLIT_DEBUG_INFO

int ROAMTriangle::_numTriangles = 0;

ROAMTriangle::ROAMTriangle(ROAMTriangle*parent):
    _error(0), _parent(parent), _diamond(NULL)
{
    _id = _numTriangles++;
}

ROAMTriangle::ROAMTriangle(glm::vec3 a, glm::vec3 b, glm::vec3 c):
    _error(0), _parent(NULL), _diamond(NULL)
{
    _id = _numTriangles++;
    _verts[0] = a.x;
    _verts[1] = a.y;
    _verts[2] = a.z;
    _verts[3] = b.x;
    _verts[4] = b.y;
    _verts[5] = b.z;
    _verts[6] = c.x;
    _verts[7] = c.y;
    _verts[8] = c.z;
}

float ROAMTriangle::getSplitPriority(glm::vec3 pos) {
    // // compute error
    // //glm::vec3 midpoint = (Util::aToVec3(_verts)+Util::aToVec3(_verts+6));
    // glm::vec3 midpoint = glm::vec3((_verts[0]+_verts[6])/2,
    // 				   (_verts[1]+_verts[7])/2,
    // 				   (_verts[2]+_verts[8])/2);
    // float error = fabs(glm::length(midpoint) - p->altitude(glm::normalize(midpoint)));

    // Node: visible error calculation should take into account whether or not this triangle
    // is in the render frame, and return 0 if it isn't. TODO
    
    float distance = 1000; //glm::length(midpoint-pos); // TODO
    //printf("visible error is %f/%f = %f\n", error, distance, error/distance);
    
    return _error/distance;
}

void ROAMTriangle::updateError(Planet*p) {
    glm::vec3 midpoint = glm::vec3((_verts[0]+_verts[6])/2,
				   (_verts[1]+_verts[7])/2,
				   (_verts[2]+_verts[8])/2);
    float altAtMidpoint = p->altitude(glm::normalize(midpoint));
    _error = fabs(glm::length(midpoint) - altAtMidpoint);
}

void ROAMTriangle::draw() {	// TODO this can be hella optimized
    glBegin(GL_TRIANGLES);

    glm::vec3 o = Util::aToVec3(_verts);
    glm::vec3 u = Util::aToVec3(_verts+3)-o;
    glm::vec3 v = Util::aToVec3(_verts+6)-o;

    glm::vec3 normal = glm::normalize(glm::cross(u,v));
    glNormal3f(normal.x, normal.y, normal.z);
    
    glVertex3f(_verts[0], _verts[1], _verts[2]);
    glVertex3f(_verts[3], _verts[4], _verts[5]);
    glVertex3f(_verts[6], _verts[7], _verts[8]);

    glEnd();

#ifdef TRIANGLE_DRAW_IDS
    glColor3f(1,.2,.2);
    glRasterPos3f((_verts[0]+_verts[3]+_verts[6])/3,
		  (_verts[1]+_verts[4]+_verts[7])/3,
		  (_verts[2]+_verts[5]+_verts[8])/3);
    char buf[8] = "abcdefg";
    snprintf(buf,sizeof(buf),"%d",_id);
    glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)buf);

    glm::vec3 middle = glm::vec3((_verts[0]+_verts[3]+_verts[6])/3,
				 (_verts[1]+_verts[4]+_verts[7])/3,
				 (_verts[2]+_verts[5]+_verts[8])/3);
    
    glRasterPos3f(((_verts[0]+_verts[3])/2+middle.x)/2,
		  ((_verts[1]+_verts[4])/2+middle.y)/2,
		  ((_verts[2]+_verts[5])/2+middle.z)/2);
    snprintf(buf,sizeof(buf),"%d",_edges[0]?_edges[0]->_id:-1);
    glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)buf);

    glRasterPos3f(((_verts[3]+_verts[6])/2+middle.x)/2,
    		  ((_verts[4]+_verts[7])/2+middle.y)/2,
    		  ((_verts[5]+_verts[8])/2+middle.z)/2);
    snprintf(buf,sizeof(buf),"%d",_edges[1]?_edges[1]->_id:-1);
    glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)buf);

    glRasterPos3f(((_verts[6]+_verts[0])/2+middle.x)/2,
    		  ((_verts[7]+_verts[1])/2+middle.y)/2,
    		  ((_verts[8]+_verts[2])/2+middle.z)/2);
    snprintf(buf,sizeof(buf),"%d",_edges[2]?_edges[2]->_id:-1);
    glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)buf);

#endif
}

int ROAMTriangle::split(PlanetRenderer*pr) {
    int numSplits = 1;
#ifdef PRINT_SPLIT_DEBUG_INFO
    std::cout << "Splitting: " << this << ", with other: " << _edges[2] << "\n";
#endif
    
    // We're not in a square, so the other triangle needs to split first
    if (_edges[2]->_edges[2] != this) {	// && _edges[2]->_edges[2]->_edges[2] != this) {
#ifdef PRINT_SPLIT_DEBUG_INFO
	std::cout << "  edge2: " << _edges[2] << " edge2->edge2: " << _edges[2]->_edges[2] << "\n";
#endif
	numSplits += _edges[2]->split(pr);
	if (_edges[2]->_edges[2] != this) {
	    printf("ERROR: BAD SPLIT PERFORMED??\n");
	    std::cout << "  edge2: " << _edges[2] << " edge2->edge2: " << _edges[2]->_edges[2] << "\n";
	    exit(0);
	}
    }

    // store vertices; first three are our first three, fourth is _edges[2]'s second
    glm::vec3 verts[4] = {
	Util::aToVec3(_verts),
	Util::aToVec3(_verts+3),
	Util::aToVec3(_verts+6),
	Util::aToVec3(_edges[2]->_verts+3)
    };

#if 1 				// TODO MAKE THIS #IF 1 WHEN STOP USING GRID
    // find new vertex; its vector is through the midpoint of our hypotenuse
    glm::vec3 newVert = glm::normalize(verts[0]+verts[2]);
    // TODO: use planet to determine proper scaling factor for newVert
    //float altitude = pr->_planet->altitude();
    float altitude = 6000;
    newVert *= altitude;
#else
    glm::vec3 newVert = Util::mulvec3(verts[0]+verts[2],.5);
#endif
    
    // create diamond and assign references and stuff
    ROAMDiamond*diamond = new ROAMDiamond(this, _edges[2],
					  new ROAMTriangle(this),
					  new ROAMTriangle(_edges[2]));
    // diamond->_parents[0] = this;
    // diamond->_parents[1] = _edges[2];
    // diamond->_children[0] = new ROAMTriangle(this, diamond);
    // diamond->_children[1] = new ROAMTriangle(_edges[2], diamond);
    // _diamond = diamond;
    // _edges[2]->_diamond = diamond;
    // diamond->_children[0]->_diamond = diamond;
    // diamond->_children[1]->_diamond = diamond;

    // store triangles and old edges
    ROAMTriangle*curr = this;
    ROAMTriangle*othr = _edges[2];
    ROAMTriangle*new0 = diamond->_children[0];
    ROAMTriangle*new1 = diamond->_children[1];

    ROAMTriangle*oldEdges[] = {
	_edges[0], _edges[1], _edges[2]->_edges[0], _edges[2]->_edges[1]
    };

#ifdef PRINT_SPLIT_DEBUG_INFO
    std::cout << "  oldEdges: [";
    for (int i = 0; i < 4; i++) {
	std::cout << oldEdges[i] << ", ";
    }
    std::cout << "]\n";
#endif
    
    // reposition triangle vertices
    Util::vec3ToA(verts[1], curr->_verts);
    Util::vec3ToA(newVert,  curr->_verts+3);
    Util::vec3ToA(verts[0], curr->_verts+6);
    
    Util::vec3ToA(verts[2], new0->_verts);
    Util::vec3ToA(newVert,  new0->_verts+3);
    Util::vec3ToA(verts[1], new0->_verts+6);

    Util::vec3ToA(verts[3], othr->_verts);
    Util::vec3ToA(newVert,  othr->_verts+3);
    Util::vec3ToA(verts[2], othr->_verts+6);
    
    Util::vec3ToA(verts[0], new1->_verts);
    Util::vec3ToA(newVert,  new1->_verts+3);
    Util::vec3ToA(verts[3], new1->_verts+6);

    // modify surrounding triangles' edges
    for (int i = 0; i < 3; i++) {
	if (curr->_edges[1]->_edges[i] == curr)
	    curr->_edges[1]->_edges[i] = new0;
    }
    for (int i = 0; i < 3; i++) {
	if (othr->_edges[1]->_edges[i] == othr)
	    othr->_edges[1]->_edges[i] = new1;
    }

    // reposition triangle edges
    curr->_edges[0] = new0;
    curr->_edges[1] = new1;
    curr->_edges[2] = oldEdges[0];
    new0->_edges[0] = othr;
    new0->_edges[1] = curr;
    new0->_edges[2] = oldEdges[1];
    othr->_edges[0] = new1;
    othr->_edges[1] = new0;
    othr->_edges[2] = oldEdges[2];
    new1->_edges[0] = curr;
    new1->_edges[1] = othr;
    new1->_edges[2] = oldEdges[3];

    // update triangle errors
    curr->updateError(pr->_planet);
    othr->updateError(pr->_planet);
    new0->updateError(pr->_planet);
    new1->updateError(pr->_planet);
    
    // add new triangles and diamond to list
    pr->_triangles->push_front(new0);
    pr->_triangles->push_front(new1);
    pr->_diamonds->push_front(diamond);

#ifdef PRINT_SPLIT_DEBUG_INFO
    // std::cout << "Splitted. New status:\n";
    // std::list<ROAMTriangle*>::iterator i;
    // for (i = pr->_triangles->begin(); i != pr->_triangles->end(); i++) {
    // 	std::cout << "  " << (*i) << "\n";
    // }

    std::cout << "  Splitted. Current status:\n";
    std::cout << "  curr: " << curr << "\n";
    std::cout << "  new0: " << new0 << "\n";
    std::cout << "  othr: " << othr << "\n";
    std::cout << "  new1: " << new1 << "\n";
#endif

    return numSplits;
}

std::ostream&operator<<(std::ostream&strm, const ROAMTriangle*t) {
    return strm << "Triangle#" << t->_id << "[" << "("
	// "("<<t->_verts[0]<<", "<<t->_verts[1]<<", "<<t->_verts[2]<<"), "
	// "("<<t->_verts[3]<<", "<<t->_verts[4]<<", "<<t->_verts[5]<<"), "
	// "("<<t->_verts[6]<<", "<<t->_verts[7]<<", "<<t->_verts[8]<<")"
		<<(t->_edges[0] ? t->_edges[0]->_id : -1)<<", "
		<<(t->_edges[1] ? t->_edges[1]->_id : -1)<<", "
		<<(t->_edges[2] ? t->_edges[2]->_id : -1)<<")" << "]";
}

ROAMDiamond::ROAMDiamond(ROAMTriangle*p1,ROAMTriangle*p2,ROAMTriangle*c1,ROAMTriangle*c2):
    _oldError(p1->_error)
{
    _parents[0] = p1;
    _parents[1] = p2;
    _children[0] = c1;
    _children[1] = c2;
    p1->_diamond = this;
    p2->_diamond = this;
    c1->_diamond = this;
    c2->_diamond = this;
}

float ROAMDiamond::getMergePriority(glm::vec3 pos) {
    return _parents[0]->getSplitPriority(pos);
}

void ROAMDiamond::merge(PlanetRenderer*pr) {
    // TODO
}
