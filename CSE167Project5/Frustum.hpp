//
//  Frustum.hpp
//  CSE167 Spring 2015 Starter Code
//
//  Created by Victor Alor on 11/1/15.
//  Copyright © 2015 RexWest. All rights reserved.
//

#ifndef Frustum_hpp
#define Frustum_hpp
#include "Camera.h"
#include "Vector4.h"
#include <stdio.h>
#include <math.h>
#include "BoundingSphere.hpp"
#include <vector>
#include <iostream>
class Frustum{
private:
    
    enum {
        TOP = 0, BOTTOM, LEFT,
        RIGHT, NEARP, FARP
    };

    
    float ratio;
    float nearD;
    float farD;
    float angle;
    
    float nh;
    float nw;
    float fh;
    float fw;
    float tang;
    float calcDistance(Vector3 a[3],Vector3);
    
public:
    static enum {OUTSIDE, INTERSECT, INSIDE};
    
    float sphereFactorX, sphereFactorY;
    Vector3 ntl,ntr,nbl,nbr,ftl,ftr,fbl,fbr,X,Y,Z,camPos;
    int contains(BoundingShpere sub,Matrix4);
    void setCamDef(Vector3 p, Vector3 l,Vector3 u);
    void update(Camera c,float nearDist,float farDist,float fov,float ratio);
    void drawPoints();
    void drawLines();
    void drawPlanes();
    void drawNormals();
    void display();
    void printPlanes() {
        
        for (int i = 0; i < 6; i++) {
            
            pl[i].print();
            printf("\n");
        }
    }
    class Plane{
    public:
        Vector3 normal,point;
        float d;
        void set3Points(Vector3 v0,Vector3 v1,Vector3 v2){
            Vector3 aux1,aux2;
            aux1 = v0 -v1;
            aux2 = v2 -v1;
            normal = aux2.cross(aux1);
            normal.normalizeThis();
            point = v1;
            d = -(normal.dot(point));
        }
        float distance(Vector3 point){
            return d+(normal).dot(point);
        }
        void setNormalAndPoint(Vector3 norm,Vector3 p){
            point = p;
            normal = norm;
            normal.normalizeThis();
            d = -(normal.dot(p));
        }
        void print(){
            normal.print("normal");
            point.print("point");
            std::cout<<"d "<<d<<std::endl;
        }
    };
     Plane pl[6];
   
};
#endif /* Frustum_hpp */
