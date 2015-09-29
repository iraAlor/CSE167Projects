#include "Sphere.h"

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif


Sphere::Sphere(double radius, int slices, int stacks) : Drawable()
{
    this->radius = radius;
    this->slices = slices;
    this->stacks = stacks;
    velocity = Vector3(-1,.56,.22);
}

void Sphere::draw(DrawData& data)
{
    material.apply();
    
    glMatrixMode(GL_MODELVIEW);
    
    glPushMatrix();
    glMultMatrixf(toWorld.ptr());
    
    glutSolidSphere(radius, slices, stacks);
    
    glPopMatrix();
}

void Sphere::reset(){
     velocity = Vector3(1,.56,.22);
    toWorld.identity();
}

void Sphere::update(UpdateData& data){
    //
    Matrix4 trans;
    

    float x  = toWorld.get(3,0);
    float y  = toWorld.get(3,1);
    float z  = toWorld.get(3,2);

    float w = 12;
    float h = 12;
    float in = 10;
    float d0 = fabs(in-z);
    float d1 = fabs((w-x));
    float d2 = fabs((h-y));
    float d3 = fabs(-in-z);
    float d4 = fabs(-w-x);
    float d5 = fabs(-h-y);
 
    if((radius>=d0 ||radius>=d3 )){
        velocity[2]*=(-.95);
    }
    if((radius>=d1 || radius>=d4) && fabs(velocity[0])>.001 ){
        velocity[0]*=(-.95);
    }
    if((radius>=d2 || radius>=d5) && fabs(velocity[1])>.005 ){
        velocity[1] *=(-.95);
    }
    if(fabs(velocity[2])<.01){
        velocity[2] = 0;
    }
    if(fabs(velocity[1])<.01){
        velocity[1] = 0;
    }
    if(fabs(velocity[0])<.01){
        velocity[0] = 0;
    }
    if(radius>=d5 && fabs(velocity[1])>.005){
        velocity[1]+=.002;
    }
    
 

    trans.makeTranslate(velocity[0], velocity[1],velocity[2]);
    toWorld = (toWorld*trans);
   // toWorld.print("");
    
}


