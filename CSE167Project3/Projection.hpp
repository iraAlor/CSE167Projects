//
//  Projection.hpp
//  CSE167 Spring 2015 Starter Code
//
//  Created by Victor Alor on 10/11/15.
//  Copyright © 2015 RexWest. All rights reserved.
//

#ifndef Projection_hpp
#define Projection_hpp

#include <stdio.h>
#include <stdio.h>
#include "Matrix4.h"
#include "Vector3.h"
#include <math.h>
class Projection{

    
public:
    Projection();
    Matrix4 projection;
    Projection(float fov,float aspect,float near,float far);
    Projection(float left,float right,float bottom,float top,float near,float far);
    void update(float left,float right,float bottom,float top,float near,float far);
    void update(float fov,float aspect,float near,float far);
};

#endif /* Projection_hpp */
