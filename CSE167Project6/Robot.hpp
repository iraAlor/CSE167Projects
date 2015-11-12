//
//  Robot.hpp
//  CSE167 Spring 2015 Starter Code
//
//  Created by Victor Alor on 10/31/15.
//  Copyright © 2015 RexWest. All rights reserved.
//

#ifndef Robot_hpp
#define Robot_hpp

#include <stdio.h>
#include "Cube.h"
#include "Sphere.hpp"
#include "Group.hpp"
#include "MatrixTransform.hpp"
#include "Appendage.hpp"
#include <GLUT/glut.h>
class Robot : public Group{
protected:
    /*
    MatrixTransform * left;
    MatrixTransform * right;
    MatrixTransform * head;
    MatrixTransform * body;
     */
public:
    float size;
    Robot();
    Robot(float sRad,float cL);
    void draw(Matrix4 m) override;
   // void draw(Matrix4);
    
};
#endif /* Robot_hpp */
