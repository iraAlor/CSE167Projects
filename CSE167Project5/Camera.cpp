#include "Camera.h"
#include <iostream>
Camera::Camera()
{
    c.identity();
    e.set(0.0, 0.0, 20.0);
    d.set(0.0, 0.0, 0.0);
    up.set(0.0, 1.0, 0.0);
    
    //Pre-define a camera matrix (and its inverse) that are shifted 'e' from the origin
    //This is used as a default camera position for Project 1
    c.set(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, e[0], e[1], e[2], 1);
    ci.set(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, -e[0], -e[1], -e[2], 1);
}

Camera::~Camera()
{
    //Delete and dynamically allocated memory/objects here
}

Matrix4& Camera::getMatrix()
{
    return c;
}

Matrix4& Camera::getInverseMatrix()
{
    return ci;
}

void Camera::update()
{
    //Update the Camera Matrix using d, e, and up
    //Solve for the z, x, and y axes of the camera matrix
    //Use these axes and the e vector to create a camera matrix c
    //Use c to solve for an inverse camera matrix ci
    Vector3 z = this->e -this->d;
    z =  z.normalize();
    Vector3 x = up.cross(z);
    x = x.normalize();
    Vector3 y = z.cross(x);
    y = y.normalize();
    c = Matrix4(x[0],x[1],x[2],0,y[0],y[1],y[2],0,z[0],z[1],z[2],0,e[0],e[1],e[2],1);
    //e.print("red ");
    ci = c.rigidInverse();
    //c.print("");
    //ci.print("kkk");
    
}


void Camera::reset(){
    c.identity();
    e.set(0.0, 0.0, 20.0);
    d.set(0.0, 0.0, 0.0);
    up.set(0.0, 1.0, 0.0);
    
    //Pre-define a camera matrix (and its inverse) that are shifted 'e' from the origin
    //This is used as a default camera position for Project 1
    c.set(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, e[0], e[1], e[2], 1);
    ci.set(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, -e[0], -e[1], -e[2], 1);
}

void Camera::set(Vector3& e, Vector3& d, Vector3& up)
{
    this->e = e;
    this->d = d;
    this->up = up;
    update();
}
void Camera::invert(){
    this->up=this->up*-1;
    update();
}
void Camera::tilt(float rads){
    float y = this->up[1];
    float angle = asinf(y)+rads;
    if(angle>6.28319){
        angle-=6.28319;
    }
   // std::cout<<"angle "<<angle<<std::endl;
    this->up[1] = sinf(angle);
    this->up[0] = cosf(angle);
    update();
    up.print("");
    
    
    
}
void Camera::rotateX(float delta) {
    Matrix4 rot;
    rot.makeRotateX(delta);
    e = rot*e;
    up = rot*up;
    //d = rot*d;
    update();
}
void Camera::rotateY(float delta){
    Matrix4 rot;
    rot.makeRotateY(delta);
    e = rot*e;
    up = rot*up;
    //d = rot*d;
    update();
}
void Camera::rotateZ(float delta){
    Matrix4 rot;
    rot.makeRotateZ(delta);
    e = rot*e;
    up = rot*up;
    //d = rot*d;
    update();
}

void Camera::scale(float delta){
    Matrix4 rot;
    rot.makeScale(delta);
    e = rot*e;
   // d = rot*d;
   // e.print("cam");
    update();
}

void Camera::move(int axis,float amount){
    if(axis<0 || axis>2){
        return;
    }
    this->e[axis]+=amount;
    this->d[axis]+=amount;
    update();
}
void Camera::changeFocus(int axis,float amount){
    if(axis<0 || axis>2){
        return;
    }
    this->e[axis]+=amount;
    update();
}
void Camera::changePos(int axis,float amount){
    if(axis<0 || axis>2){
        return;
    }
    this->e[axis]+=amount;
    update();
}
