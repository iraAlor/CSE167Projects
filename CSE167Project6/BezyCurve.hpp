//
//  BezyCurve.hpp
//  CSE167 Spring 2015 Starter Code
//
//  Created by Victor Alor on 11/8/15.
//  Copyright © 2015 RexWest. All rights reserved.
//

#ifndef BezyCurve_hpp
#define BezyCurve_hpp
#include "Matrix4.h"
#include <vector>
#include <stdio.h>
#include "Texture.h"
class BezyCurve{
private:
    Vector4 genVec(float val);
    Matrix4 bezyMat;
    Matrix4 bezyX;
    Matrix4 bezyY;
    Matrix4 bezyZ;
    Matrix4 bezyX1;
    Matrix4 bezyY1;
    Matrix4 bezyZ1;
    bool mode;
    Vector3 calcPoint(float u,float v);
    Vector3 calcNormal(float u,float v);
    Vector3 calcPoint2(float,float);
    Vector3 calcNormal2(float,float);
    std::vector<std::vector<Vector3>> quads;
    void drawOne();
    void drawTwo();
    int level;
    float dt;
    float time;
    Matrix4 toWorld;
    Matrix4 x0;
    Matrix4 y0;
    Matrix4 z0;
    Matrix4 x1;
    Matrix4 y1;
    Matrix4 z1;
public:
    BezyCurve(Matrix4,Matrix4,Matrix4,int);
    void render();
    void init();
    void update();
    void setSecond(Matrix4,Matrix4,Matrix4);
    Texture * tex;
    
};
#endif /* BezyCurve_hpp */
