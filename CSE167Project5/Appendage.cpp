//
//  Appendage.cpp
//  CSE167 Spring 2015 Starter Code
//
//  Created by Victor Alor on 11/1/15.
//  Copyright © 2015 RexWest. All rights reserved.
//

#include "Appendage.hpp"
#include <iostream>
Appendage::Appendage(float delta){
    this->angle = 0;
    this->delta = delta;
    transform.makeRotateX(delta);
    
}

void Appendage::update(){
    angle+=delta;
 //bbbstd::cout<<"MY angle is "<<angle<<std::endl;
    if(fabs(angle)>=45){
        delta*=-1;
       // transform.makeRotateX(delta);
        //std::cout<<"MY Delta is "<<delta<<std::endl;
    }
   transform.makeRotateX(angle*M_PI/180.0);
    
}