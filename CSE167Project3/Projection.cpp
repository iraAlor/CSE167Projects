//
//  Projection.cpp
//  CSE167 Spring 2015 Starter Code
//
//  Created by Victor Alor on 10/11/15.
//  Copyright © 2015 RexWest. All rights reserved.
//

#include "Projection.hpp"
#include <stdio.h>
#include "Matrix4.h"
#include "Vector3.h"
#include <math.h>
static float deg2Rad(float deg){
    
    return deg*0.0174532925;
}
Projection::Projection(){
    projection.identity();
}
Projection::Projection(float fov,float aspect,float near,float far){
    this->update(fov,aspect,near,far);
}
Projection::Projection(float left,float right,float bottom,float top,float near,float far){
    this->update(left, right, bottom, top, near, far);
}
void Projection::update(float left,float right,float bottom,float top,float near,float far){
    projection.identity();
    
    projection.set(0,0,(2*near)/(right -left));
    projection.set(1,1,(2*near)/(top-bottom));
    projection.set(2,0,(right+left)/(right-left));
    projection.set(2,1,(top+bottom)/(top-bottom));
    projection.set(2,2,-(far+near)/(far-near));
    projection.set(2,3,-1);
    projection.set(3,2,-2*far*near/(far-near));
    projection.set(3,3,0);
    
    
}
void Projection::update(float fov,float aspect,float near,float far){
    fov =  (fov/180.0)*M_PI;
    projection.set(
          1/(aspect*(tan(fov/2.0))),0.0,0.0,0.0,
          0.0,1/(tan(fov/2.0)),0.0,0.0,
          0.0,0.0,(near+ far)/(near - far),-1.0,
          0.0,0.0, (2.0 * near * far)/(near - far),0.0);

}

