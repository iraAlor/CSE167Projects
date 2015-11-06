//
//  Platoon.hpp
//  CSE167 Spring 2015 Starter Code
//
//  Created by Victor Alor on 11/2/15.
//  Copyright © 2015 RexWest. All rights reserved.
//

#ifndef Platoon_hpp
#define Platoon_hpp

#include <stdio.h>
#include "Robot.hpp"
#define MAXSTEPS 400
class Platoon : public Group{
private:
  
    float firstOne;
public:
    Robot * robo;
      Matrix4 rot;
    bool start;
    int mode;
    enum{ROTATE1,ROTATE2,ROTATE3,ROTATE4,ROTATE5,TRANSLEFT,TRANSRIGHT,TRANSUP,TRANSDOWN};
    Platoon();
    Platoon(int col,int num,Robot * robo,float center);
    int col;
    int row;
    float center;
    void draw(Matrix4);
    virtual void update();
    void update1();
    void update2();
    float counter;
    int dir;
    void setRotation(int part);
    void reset();
    float otherCounter;
};

#endif /* Platoon_hpp */
