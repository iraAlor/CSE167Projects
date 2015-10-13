//
//  ViewPort.hpp
//  CSE167 Spring 2015 Starter Code
//
//  Created by Victor Alor on 10/11/15.
//  Copyright © 2015 RexWest. All rights reserved.
//

#ifndef ViewPort_hpp
#define ViewPort_hpp

#include <stdio.h>
#include "Matrix4.h"
#include "Vector3.h"
#include <math.h>

class ViewPort{
protected:
     Matrix4 port;
    
public:
    ViewPort();
    ViewPort(float x,float y);
    Matrix4& getMatrix();
    void update(float x0,float x1,float y0,float y1);
    void update(float x,float y);
    ViewPort(float x0,float x1,float y0,float y1);
};
#endif /* ViewPort_hpp */
