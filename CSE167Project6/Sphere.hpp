//
//  Sphere.hpp
//  CSE167 Spring 2015 Starter Code
//
//  Created by Victor Alor on 10/31/15.
//  Copyright © 2015 RexWest. All rights reserved.
//

#ifndef Sphere_hpp
#define Sphere_hpp

#include <stdio.h>
#include "Geode.hpp"
#include "Vector3.h"
#include "Vector4.h"
#include <GLUT/glut.h>
class Sphere : public Geode{
private:
    float radius;
    int slices;
    int stacks;
    Vector4 state;
public:
    Sphere(float radius,int slices,int stacks);
    void render();
    
};
#endif /* Sphere_hpp */
