//
//  BoundingSphere.hpp
//  CSE167 Spring 2015 Starter Code
//
//  Created by Victor Alor on 11/1/15.
//  Copyright © 2015 RexWest. All rights reserved.
//

#ifndef BoundingSphere_hpp
#define BoundingSphere_hpp

#include <stdio.h>
#include "Vector3.h"
#include "Matrix4.h"
#include "Vector4.h"
#include <GLUT/glut.h>
#include "Material.h"
class BoundingShpere{
protected:
   
   
    
public:
    Material mat;
    float radius;
    Matrix4 tempMat;
    Vector4 coordinates;
    Vector4 tempCoord;
    void display();
    void display(Matrix4);

    BoundingShpere();
    BoundingShpere(Vector4,float);
    BoundingShpere(BoundingShpere*);
    void set(Matrix4);
    
};

#endif /* BoundingSphere_hpp */
