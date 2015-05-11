#include "ROAM.hpp"

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
