#ifndef ROAM_H
#define ROAM_H

#include "Util.hpp"
#include "Planet.hpp"
//#include "PlanetRenderer.hpp"

class ROAMDiamond;
class PlanetRenderer;

class ROAMTriangle {    
public:
    float _error;

    GLfloat _verts[9];
    ROAMTriangle*_edges[3];
    ROAMTriangle*_parent;
    ROAMDiamond*_diamond;

    int _id;
    static int _numTriangles;
    
    ROAMTriangle(ROAMTriangle*parent); // for split
    ROAMTriangle(glm::vec3 a, glm::vec3 b, glm::vec3 c); // for the main 12
    
    float getSplitPriority(glm::vec3 pos, glm::vec3 dir);
    void draw();
    void updateError(Planet*p);	// updates the cached error

    // split returns the number of splits performed
    int split(PlanetRenderer*pr);

    bool isInSquare();
    bool isInDiamond();
    
    friend std::ostream&operator<<(std::ostream&strm, const ROAMTriangle*t);
};

class ROAMDiamond {
public:
    ROAMTriangle*_parents[2];
    ROAMTriangle*_children[2];
    float _oldError;

    ROAMDiamond(ROAMTriangle*p1,ROAMTriangle*p2,ROAMTriangle*c1,ROAMTriangle*c2);
    float getMergePriority(glm::vec3 pos, glm::vec3 dir);
    void merge(PlanetRenderer*pr);

    void disconnectAndDelete();
    ~ROAMDiamond();
    
    friend std::ostream&operator<<(std::ostream&strm, const ROAMDiamond*d);
};

#endif
