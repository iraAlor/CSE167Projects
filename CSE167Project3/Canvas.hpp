//
//  Canvas.hpp
//  CSE167 Spring 2015 Starter Code
//
//  Created by Victor Alor on 10/11/15.
//  Copyright © 2015 RexWest. All rights reserved.
//

#ifndef Canvas_hpp
#define Canvas_hpp

#include <stdio.h>
#include "Matrix4.h"
#include "Vector3.h"
#include "Vector4.h"
#include <math.h>
#include <vector>
#include "OBJObject.h"
#include "Camera.h"
#include <iostream>
#include <time.h>
#include <stdlib.h> 



class Canvas{
protected:
    float* pixels;
    float* zbuff;
    float size;
    float width;
    float height;
    
    
public:
    int rastMode;
    bool debug;
    Canvas();
    Canvas(int x,int y);
    void update(int x,int y);
    void rasterVetices(OBJObject*,Matrix4,Matrix4&);
    float& operator [] (int);
    float * getArr();
    void clear();
    void rasterTriangles(OBJObject * obj,Matrix4 transform,Matrix4& port);
    Vector3 getBaryCoordinates(int,int,int,int,int,int,int,int);
    Vector3 getBaryCoordinates(Vector3 a,Vector3 b,Vector3 c,Vector3 p);
    Vector4 convert(Vector4&,Matrix4&,Matrix4&);
};
#endif /* Canvas_hpp */
