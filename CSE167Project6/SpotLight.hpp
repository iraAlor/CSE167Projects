//
//  SpotLight.hpp
//  CSE167 Spring 2015 Starter Code
//
//  Created by Victor Alor on 10/29/15.
//  Copyright © 2015 RexWest. All rights reserved.
//

#ifndef SpotLight_hpp
#define SpotLight_hpp

#include <stdio.h>
#include "Light.h"
class SpotLight : public Light{
    
public:
    SpotLight(float x,float y,float z,Color amb,Color diffuse,Color specular);
    virtual void bind(int);
    virtual void unbind(int);
    Vector4 direction;
    float angle;
    virtual void rotateLight(Matrix4 rot);
    virtual void scaleLight(float dir);
    virtual void changeExp(float dir);
    virtual void changeFOV(float  dir);
    void centerSpotLight();
    float exp;
    float fov;
};
#endif /* SpotLight_hpp */
