//
//  BoundingSphere.cpp
//  CSE167 Spring 2015 Starter Code
//
//  Created by Victor Alor on 11/1/15.
//  Copyright © 2015 RexWest. All rights reserved.
//

#include "BoundingSphere.hpp"
BoundingShpere::BoundingShpere(){
    BoundingShpere(Vector4(0,0,0,1),10);
}
BoundingShpere::BoundingShpere(Vector4 coord,float rad){
    this->coordinates = coord;
    this->radius = rad;
}
BoundingShpere::BoundingShpere(BoundingShpere* orig){
    this->coordinates = orig->coordinates;
    this->radius = orig->radius;
    this->tempMat = orig->tempMat;
    this->tempCoord = orig->tempMat*Vector4(0,0,0,1);
}
void BoundingShpere::set(Matrix4 m){
    this->tempMat = m;
    this->tempCoord = m*Vector4(0,0,0,1);
}
void BoundingShpere::display(){
    //Vector4 nc = c*this->coordinates;
    mat.apply();
    glMatrixMode(GL_MODELVIEW);
    
    //Push a save state onto the matrix stack, and multiply in the toWorld matrix
    glPushMatrix();
    glMultMatrixf(tempMat.ptr());
    glutWireSphere(radius, 10, 10);
    glPopMatrix();

}
void BoundingShpere::display(Matrix4 m){
    //Vector4 nc = c*this->coordinates;
   // mat.apply();
    glMatrixMode(GL_MODELVIEW);
    
    //Push a save state onto the matrix stack, and multiply in the toWorld matrix
    glPushMatrix();
    glMultMatrixf(m.ptr());
    glutWireSphere(radius, 10, 10);
    glPopMatrix();
    
}