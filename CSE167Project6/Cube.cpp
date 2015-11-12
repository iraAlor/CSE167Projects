#include "Cube.h"

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

#include "Window.h"
#include "math.h"
#include "Vector3.h"
Cube::Cube(float len){
     this->material = Material(Color(0.329412f, 0.223529f, 0.027451f), Color(0.780392f, 0.568627f, 0.113725f), Color(0.992157f, 0.941176f, 0.807843f),Color::emissionMaterialDefault(),Color::red() ,27.8974f);
    this->length = len;
}
void Cube::render(){
    glutSolidCube(length);
}

