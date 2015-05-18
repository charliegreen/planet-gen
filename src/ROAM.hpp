#ifndef ROAM_H
#define ROAM_H

#include "Util.hpp"
#include "Planet.hpp"
//#include "PlanetRenderer.hpp"

class ROAMDiamond;
class PlanetRenderer;

class ROAMTriangle {
public:
    GLfloat _verts[9];
    ROAMTriangle*_edges[3];
    ROAMTriangle*_parent;
    ROAMDiamond*_diamond;

    int _id;
    static int _numTriangles;
    
    ROAMTriangle(ROAMTriangle*parent, ROAMDiamond*diamond); // for split
    ROAMTriangle(glm::vec3 a, glm::vec3 b, glm::vec3 c); // for the main 12
    
    float getSplitPriority(Planet*p, glm::vec3 pos);
    //void getVertArray(GLfloat*array);
    void draw();

    // split returns the number of splits performed
    int split(PlanetRenderer*pr);

    friend std::ostream&operator<<(std::ostream&strm, const ROAMTriangle*t);
};

class ROAMDiamond {
public:
    ROAMTriangle*_parents[2];
    ROAMTriangle*_children[2];

    float getMergePriority(glm::vec3 pos);
};

#endif
