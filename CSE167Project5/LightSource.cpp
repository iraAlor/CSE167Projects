//
//  LightSource.cpp
//  CSE167 Spring 2015 Starter Code
//
//  Created by Victor Alor on 10/14/15.
//  Copyright © 2015 RexWest. All rights reserved.
//

#include "LightSource.hpp"
#include <iostream>
LightSource::LightSource(float x,float y,float z,float r,float g,float b){
    this->coord = Vector3(x,y,z);
    this->color = Vector3(r,g,b);
    
    
}
LightSource::LightSource(){
    LightSource(10,15,16,1,1,1);
    coord =  Vector3(7,7,8);
    color = Vector3(1,1,1);
}
LightSource::LightSource(float x,float y,float z){
    
    LightSource(x,y,z,1,1,1);
}

Vector3 LightSource::getL(Vector3 destination){
   return (destination - coord).normalize();
    
}
Vector3 LightSource::getC(Vector3 destination){
    Vector3 temp = color*(1/((destination -coord).magnitude()*(destination -coord).magnitude()));
   
    return temp;
}
