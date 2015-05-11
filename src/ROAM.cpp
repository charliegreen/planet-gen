#include "ROAM.hpp"
#include "PlanetRenderer.hpp"

ROAMTriangle::ROAMTriangle(ROAMTriangle*parent, ROAMDiamond*diamond):
    _parent(parent), _diamond(diamond)
{}
    
ROAMTriangle::ROAMTriangle(glm::vec3 a, glm::vec3 b, glm::vec3 c):
    _parent(NULL), _diamond(NULL)
{
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

float ROAMTriangle::getSplitPriority(glm::vec3 pos) { // TODO
    return 0;
}

void ROAMTriangle::draw() {	// TODO this can be hella optimized
    glBegin(GL_TRIANGLES);
    glColor3f(.1,.2,.3);

    glVertex3f(_verts[0], _verts[1], _verts[2]);
    glVertex3f(_verts[3], _verts[4], _verts[5]);
    glVertex3f(_verts[6], _verts[7], _verts[8]);

    glEnd();
}

float ROAMDiamond::getMergePriority(glm::vec3 pos) { // TODO
    return 0;
}

void ROAMTriangle::split(PlanetRenderer*pr) {
    if (!_edges[2] || _edges[2]->_edges[2] != this) {
	printf("Cannot split triangle that is not part of a square\n");
	return;
    }

    // store vertices; first three are our first three, fourth is _edges[2]'s second
    glm::vec3 verts[4] = {
	Util::aToVec3(_verts),
	Util::aToVec3(_verts+3),
	Util::aToVec3(_verts+6),
	Util::aToVec3(_edges[2]->_verts+3)
	// glm::vec3(_verts[0], _verts[1], _verts[2]),
	// glm::vec3(_verts[3], _verts[4], _verts[5]),
	// glm::vec3(_verts[6], _verts[7], _verts[8]),
	// glm::vec3(_edges[2]->_verts[3], _edges[2]->_verts[4], _edges[2]->_verts[5])
    };
    
    // find new vertex; its vector is through the midpoint of our hypotenuse
    glm::vec3 newVert = glm::normalize(verts[0]+verts[2]);

    // TODO: use planet to determine proper scaling factor for newVert
    //float altitude = pr->_planet->altitude();
    float altitude = 6000;
    newVert *= altitude;
    
    // create diamond and assign all references
    ROAMDiamond*diamond = new ROAMDiamond();
    diamond->_parents[0] = this;
    diamond->_parents[1] = _edges[2];
    diamond->_children[0] = new ROAMTriangle(this, diamond);
    diamond->_children[1] = new ROAMTriangle(_edges[2], diamond);

    _diamond = diamond;
    _edges[2]->_diamond = diamond;
    diamond->_children[0]->_diamond = diamond;
    diamond->_children[1]->_diamond = diamond;

    // reposition triangles and edges
    Util::vec3ToA(verts[1], _verts);
    Util::vec3ToA(newVert,  _verts+3);
    Util::vec3ToA(verts[0], _verts+6);
    
    Util::vec3ToA(verts[2], diamond->_children[0]->_verts);
    Util::vec3ToA(newVert,  diamond->_children[0]->_verts+3);
    Util::vec3ToA(verts[1], diamond->_children[0]->_verts+6);

    Util::vec3ToA(verts[3], _edges[2]->_verts);
    Util::vec3ToA(newVert,  _edges[2]->_verts+3);
    Util::vec3ToA(verts[2], _edges[2]->_verts+6);
    
    Util::vec3ToA(verts[0], diamond->_children[1]->_verts);
    Util::vec3ToA(newVert,  diamond->_children[1]->_verts+3);
    Util::vec3ToA(verts[3], diamond->_children[1]->_verts+6);

    // add new triangles to display list
    pr->_triangles->push_front(diamond->_children[0]);
    pr->_triangles->push_front(diamond->_children[1]);
}
