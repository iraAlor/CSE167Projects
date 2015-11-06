//
//  General.hpp
//  CSE167 Spring 2015 Starter Code
//
//  Created by Victor Alor on 11/3/15.
//  Copyright © 2015 RexWest. All rights reserved.
//

#ifndef General_hpp
#define General_hpp

#include <stdio.h>
#include "Platoon.hpp"
#include <vector>
#define MAXSTEPS 400
class General : public Group{
public:
    int pos;
    std::vector<int> steps;
    Vector3 coord;
    float firstOne;
    static enum{ROTATE1,ROTATE2,ROTATE3,ROTATE4,ROTATE5,TRANSLEFT,TRANSRIGHT,TRANSUP,TRANSDOWN};
    void setSteps(std::vector<int>);
    //Platoon * plat;
    Matrix4 trans;
    Matrix4 rotLeft;
    Matrix4 currMatrix;
    float counter;
    int mode;
    void move(int,float);
    General();
    void update();
    void draw(Matrix4 m);
    void reset();
    bool firstpass;
    float otherCounter;
    
};
#endif /* General_hpp */
