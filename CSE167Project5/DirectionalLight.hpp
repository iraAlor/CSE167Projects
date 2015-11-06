//
//  DirectionalLight.hpp
//  CSE167 Spring 2015 Starter Code
//
//  Created by Victor Alor on 10/29/15.
//  Copyright © 2015 RexWest. All rights reserved.
//

#ifndef DirectionalLight_hpp
#define DirectionalLight_hpp

#include <stdio.h>
#include "Light.h"
class DirectionalLight : public Light{
    
public:
    DirectionalLight(float x,float y,float z,Color amb,Color diffuse,Color specular);
    virtual void bind(int);
    virtual void unbind(int);
    virtual void rotateLight(Matrix4 rot);
};
#endif /* DirectionalLight_hpp */
