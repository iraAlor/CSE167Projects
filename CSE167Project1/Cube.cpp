#include "Cube.h"

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

#include "Window.h"
#include "math.h"


Cube::Cube(float size) : Drawable()
{
    this->size = size;
    this->spinDir = 1;
}

Cube::~Cube()
{
    //Delete any dynamically allocated memory/objects here
}


void Cube::draw(DrawData& data)
{
    float halfSize = size/2.0;
    
    //Apply the material properties
    //From here forward anything drawn will be drawn with this material
    material.apply();
    
    //Set the OpenGL Matrix mode to ModelView (used when drawing geometry)
    glMatrixMode(GL_MODELVIEW);
    
    //Push a save state onto the matrix stack, and multiply in the toWorld matrix
    glPushMatrix();
    glMultMatrixf(toWorld.ptr());
    
    //Make cube!
    //Note: The glBegin, and glEnd should always be as close to the glNormal/glVertex calls as possible
    //These are special calls that 'freeze' many internal states of OpenGL.
    //Once the glBegin state is active many of the calls made to OpenGL (like glMultMatrixf) will be IGNORED!
    //As a good habit, only call glBegin just before you need to draw, and call end just after you finish
    glBegin(GL_QUADS);
    
    // Draw front face:
    glNormal3f(0.0, 0.0, 1.0);
    glVertex3f(-halfSize,  halfSize,  halfSize);
    glVertex3f( halfSize,  halfSize,  halfSize);
    glVertex3f( halfSize, -halfSize,  halfSize);
    glVertex3f(-halfSize, -halfSize,  halfSize);
    
    // Draw left side:
    glNormal3f(-1.0, 0.0, 0.0);
    glVertex3f(-halfSize,  halfSize,  halfSize);
    glVertex3f(-halfSize,  halfSize, -halfSize);
    glVertex3f(-halfSize, -halfSize, -halfSize);
    glVertex3f(-halfSize, -halfSize,  halfSize);
    
    // Draw right side:
    glNormal3f(1.0, 0.0, 0.0);
    glVertex3f( halfSize,  halfSize,  halfSize);
    glVertex3f( halfSize,  halfSize, -halfSize);
    glVertex3f( halfSize, -halfSize, -halfSize);
    glVertex3f( halfSize, -halfSize,  halfSize);
    
    // Draw back face:
    glNormal3f(0.0, 0.0, -1.0);
    glVertex3f(-halfSize,  halfSize, -halfSize);
    glVertex3f( halfSize,  halfSize, -halfSize);
    glVertex3f( halfSize, -halfSize, -halfSize);
    glVertex3f(-halfSize, -halfSize, -halfSize);
    
    // Draw top side:
    glNormal3f(0.0, 1.0, 0.0);
    glVertex3f(-halfSize,  halfSize,  halfSize);
    glVertex3f( halfSize,  halfSize,  halfSize);
    glVertex3f( halfSize,  halfSize, -halfSize);
    glVertex3f(-halfSize,  halfSize, -halfSize);
    
    // Draw bottom side:
    glNormal3f(0.0, -1.0, 0.0);
    glVertex3f(-halfSize, -halfSize, -halfSize);
    glVertex3f( halfSize, -halfSize, -halfSize);
    glVertex3f( halfSize, -halfSize,  halfSize);
    glVertex3f(-halfSize, -halfSize,  halfSize);
    
    glEnd();
    
    //The above glBegin, glEnd, glNormal and glVertex calls can be replaced with a glut convenience function
    //glutSolidCube(size);
    
    //Pop the save state off the matrix stack
    //This will undo the multiply we did earlier
    glPopMatrix();
}


void Cube::update(UpdateData& data)
{
    //
}

void Cube::spin(float radians)
{
    Matrix4 rotation;
    rotation.makeRotateY(radians*spinDir);
    
    toWorld = toWorld * rotation;
}

void Cube::trans(float x,float y,float z){
    
    Matrix4 trans;
    trans.makeTranslate(x, y, z);
    toWorld = trans*toWorld;
}
void Cube::reset(){
    toWorld.identity();
    spinDir = 1;
    rotRate = 0.0;
}
void Cube::rotate(float scale){
    float x = toWorld.get(3,0);
    float y = toWorld.get(3,1);
    if(x==0 && y ==0){
        return;
    }
    float r = sqrt(x*x+y*y);
    float pth = atan(y/x) + (x <0 ? -M_PI : 0);
    pth+=scale*.10;
    float nx = r*cos(pth);
    float ny = r*sin(pth);
    Matrix4 trans;
    
    trans.makeTranslate(nx-x,ny-y,0.0);
    toWorld = trans*toWorld;
}
void Cube::scale(float sFactor){
    Matrix4 scaly;
    scaly.makeScale(sFactor);
    toWorld = scaly*toWorld;
}
void Cube::printCoord(){
    toWorld.printCol(3);
    
}
