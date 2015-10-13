#include "Cube.h"

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

#include "Window.h"
#include "math.h"
#include "Vector3.h"

Cube::Cube(float size) : OBJObject()
{
    this->size = size;
    this->spinDir = 1;
    orbit.identity();
    toWorld.identity();
    float halfSize = size/2.0;
    // Draw front face:
    // Draw front face:
  
    normals->push_back(new Vector3(0,0,1));
    Vector3 * a = new Vector3(-halfSize,  halfSize,  halfSize);
    Vector3 * b = new Vector3(halfSize,  halfSize,  halfSize);
    Vector3 * c = new Vector3( halfSize, -halfSize,  halfSize);
    Vector3 * d = new Vector3( -halfSize, -halfSize,  halfSize);
    vertices ->push_back(a);
    vertices ->push_back(b);
    vertices->push_back(c);
    vertices->push_back(d);
    
    //FRONT FACE
    Face* face = new Face;
    //a-b-c
    face->vertexIndices[0] = 0;
    face->vertexIndices[1] = 1;
    face->vertexIndices[2] = 2;
    face->normalIndices[0] = 0;
    face->normalIndices[1] = 0;
    face->normalIndices[2] = 0;
    faces->push_back(face);
    
    //a-d-c
    face = new Face;
    face->vertexIndices[0] = 0;
    face->vertexIndices[1] = 3;
    face->vertexIndices[2] = 2;
    face->normalIndices[0] = face->normalIndices[1] = face->normalIndices[2] =0;
    faces->push_back(face);
    // left side
    normals->push_back(new Vector3(1.0, 0.0, 0.0));
   
   
    Vector3 * e = new Vector3(-halfSize,  halfSize, -halfSize);
    Vector3 * f = new Vector3(-halfSize, -halfSize, -halfSize);
    vertices->push_back(e);
    vertices->push_back(f);

    //e-a-d
    face = new Face;
    face->vertexIndices[0] = 4;
    face->vertexIndices[1] = 0;
    face->vertexIndices[2] = 3;
    face->normalIndices[0] = face->normalIndices[1] = face->normalIndices[2] =1;
    faces->push_back(face);
    //e-f-d
    face = new Face;
    face->vertexIndices[0] = 4;
    face->vertexIndices[1] = 5;
    face->vertexIndices[2] = 3;
    face->normalIndices[0] = face->normalIndices[1] = face->normalIndices[2] =1;
    faces->push_back(face);
    
    // Draw right side:
    normals->push_back(new Vector3(1,0,0));
    Vector3 * g = new Vector3( halfSize, -halfSize, -halfSize);
    Vector3 * h = new Vector3( halfSize,  halfSize, -halfSize);
    vertices->push_back(g);
    vertices->push_back(h);
    //c-b-h
    face = new Face;
    face->vertexIndices[0] =2;
    face->vertexIndices[1] = 1;
    face->vertexIndices[2] =7;
    face->normalIndices[0] = face->normalIndices[1] = face->normalIndices[2] =2;
    faces->push_back(face);
    //g-h-c
    face = new Face;
    face->vertexIndices[0] = 6;
    face->vertexIndices[1] = 7;
    face->vertexIndices[2] = 2;
    face->normalIndices[0] = face->normalIndices[1] = face->normalIndices[2] =2;
    faces->push_back(face);

    
    // Draw top side:
    normals->push_back(new Vector3(0.0, 1.0, 0.0));
    //e-h-b
    face = new Face;
    face->vertexIndices[0] = 4;
    face->vertexIndices[1] = 7;
    face->vertexIndices[2] = 1;
    face->normalIndices[0] = face->normalIndices[1] = face->normalIndices[2] = 3;
    faces->push_back(face);
    //e-a-b
    face = new Face;
    face->vertexIndices[0] = 4;
    face->vertexIndices[1] = 0;
    face->vertexIndices[2] = 1;
    face->normalIndices[0] = face->normalIndices[1] = face->normalIndices[2] = 3;
    faces->push_back(face);
    
    // Draw back face:
     normals->push_back(new Vector3(0.0, 0.0, -1.0));
    //e-h-g
    face = new Face;
    face->vertexIndices[0] = 4;
    face->vertexIndices[1] = 7;
    face->vertexIndices[2] = 6;
    face->normalIndices[0] = face->normalIndices[1] = face->normalIndices[2] = 4;
    faces->push_back(face);
    //e-f-g
    face = new Face;
    face->vertexIndices[0] = 4;
    face->vertexIndices[1] = 5;
    face->vertexIndices[2] = 6;
    face->normalIndices[0] = face->normalIndices[1] = face->normalIndices[2] = 4;
    faces->push_back(face);
    
    
    // Draw bottom side:
    normals->push_back(new Vector3(0.0, -1.0, 0.0));
    //f-g-c
    face = new Face;
    face->vertexIndices[0] = 5;
    face->vertexIndices[1] = 6;
    face->vertexIndices[2] = 2;
    face->normalIndices[0] = face->normalIndices[1] = face->normalIndices[2] = 5;
    faces->push_back(face);
    //f-d-c
    face = new Face;
    face->vertexIndices[0] = 5;
    face->vertexIndices[1] = 3;
    face->vertexIndices[2] = 2;
    face->normalIndices[0] = face->normalIndices[1] = face->normalIndices[2] = 5;
    faces->push_back(face);
}

Cube::~Cube()
{
    //Delete any dynamically allocated memory/objects here
}

void Cube::toggleSpin(){
    spinDir *= -1;
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
  
    Matrix4 rot;
    rot.makeRotateZ(.10*scale);
    toWorld = rot*toWorld;
    
  
}
void Cube::scale(float sFactor){
    Matrix4 scaly;
    scaly.makeScale(sFactor);
    toWorld = toWorld*scaly;
}
void Cube::printCoord(){
    toWorld.printCol(3);
    
}

