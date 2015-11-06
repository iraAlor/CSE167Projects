//
//  General2.hpp
//  CSE167 Spring 2015 Starter Code
//
//  Created by Victor Alor on 11/3/15.
//  Copyright © 2015 RexWest. All rights reserved.
//

#ifndef General2_hpp
#define General2_hpp

#include <stdio.h>
#include <stdio.h>
#include "Platoon.hpp"
#include <vector>
#define MAXSTEPS 400
class General2 : public Group{
public:
    int pos;
    bool firstpass;
    float firstOne;
    Vector3 coord;
    static enum{ROTATE1,ROTATE2,ROTATE3,ROTATE4,ROTATE5,TRANSLEFT,TRANSRIGHT,TRANSUP,TRANSDOWN};
    //Platoon * plat;
    Matrix4 trans;
    Matrix4 rotLeft;
    Matrix4 currMatrix;
    float counter;
    int mode;
    void move(int,float);
    General2();
    void update();
    void draw(Matrix4 m);
    void reset();
    
    
    
};

#endif /* General2_hpp */
