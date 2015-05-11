#ifndef ROAM_H
#define ROAM_H

#include "Util.hpp"

class ROAMDiamond;

class ROAMTriangle {
public:
    GLfloat _verts[9];
    ROAMTriangle*_edges[3];
    ROAMTriangle*_parent;
    ROAMDiamond*_diamond;

    ROAMTriangle(glm::vec3 a, glm::vec3 b, glm::vec3 c); // for the main 12
    
    float getSplitPriority(glm::vec3 pos);
    //void getVertArray(GLfloat*array);
    void draw();
};

class ROAMDiamond {
public:
    ROAMTriangle*_parents[2];
    ROAMTriangle*_children[2];

    float getMergePriority(glm::vec3 pos);
};

#endif
