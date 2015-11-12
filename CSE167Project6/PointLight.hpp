//
//  PointLight.hpp
//  CSE167 Spring 2015 Starter Code
//
//  Created by Victor Alor on 10/29/15.
//  Copyright © 2015 RexWest. All rights reserved.
//

#ifndef PointLight_hpp
#define PointLight_hpp

#include <stdio.h>
#include "Light.h"
#include "Color.h"
class PointLight : public Light{
    
public:
    PointLight(float x,float y,float z,Color ,Color,Color);
    virtual void bind(int);
    virtual void unbind(int);
    virtual void rotateLight(Matrix4 rot);
    virtual void scaleLight(float dir);
};
#endif /* PointLight_hpp */
