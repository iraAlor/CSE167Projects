#ifndef CSE167_Cube_h
#define CSE167_Cube_h
#include "Geode.hpp"
#include <GLUT/glut.h>
class Cube : public Geode{
protected:
    float length;
   
public:
    Cube(float length);
    void render();
    
};

#endif

