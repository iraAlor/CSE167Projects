//
//  Frustum.cpp
//  CSE167 Spring 2015 Starter Code
//
//  Created by Victor Alor on 11/1/15.
//  Copyright © 2015 RexWest. All rights reserved.
//

#include "Frustum.hpp"
#include <iostream>
#define HALF_ANG2RAD 3.14159265358979323846/360.0



void Frustum::drawPoints(){
    glBegin(GL_POINTS);
    
    glVertex3f(ntl[0],ntl[1],ntl[2]);
    glVertex3f(ntr[0],ntr[1],ntr[2]);
    glVertex3f(nbl[0],nbl[1],nbl[2]);
    glVertex3f(nbr[0],nbr[1],nbr[2]);;
    
    glVertex3f(ftl[0],ftl[1],ftl[2]);
    glVertex3f(ftr[0],ftr[1],ftr[2]);
    glVertex3f(fbl[0],fbl[1],fbl[2]);
    glVertex3f(fbr[0],fbr[1],fbr[2]);
    
    glEnd();
}



void Frustum::drawLines(){
    glBegin(GL_LINE_LOOP);
    //near plane
    glVertex3f(ntl[0],ntl[1],ntl[2]);
    glVertex3f(ntr[0],ntr[1],ntr[2]);
    glVertex3f(nbr[0],nbr[1],nbr[2]);
    glVertex3f(nbl[0],nbl[1],nbl[2]);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    //far plane
    glVertex3f(ftr[0],ftr[1],ftr[2]);
    glVertex3f(ftl[0],ftl[1],ftl[2]);
    glVertex3f(fbl[0],fbl[1],fbl[2]);
    glVertex3f(fbr[0],fbr[1],fbr[2]);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    //bottom plane
    glVertex3f(nbl[0],nbl[1],nbl[2]);
    glVertex3f(nbr[0],nbr[1],nbr[2]);
    glVertex3f(fbr[0],fbr[1],fbr[2]);
    glVertex3f(fbl[0],fbl[1],fbl[2]);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    //top plane
    glVertex3f(ntr[0],ntr[1],ntr[2]);
    glVertex3f(ntl[0],ntl[1],ntl[2]);
    glVertex3f(ftl[0],ftl[1],ftl[2]);
    glVertex3f(ftr[0],ftr[1],ftr[2]);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    //left plane
    glVertex3f(ntl[0],ntl[1],ntl[2]);
    glVertex3f(nbl[0],nbl[1],nbl[2]);
    glVertex3f(fbl[0],fbl[1],fbl[2]);
    glVertex3f(ftl[0],ftl[1],ftl[2]);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    // right plane
    glVertex3f(nbr[0],nbr[1],nbr[2]);
    glVertex3f(ntr[0],ntr[1],ntr[2]);
    glVertex3f(ftr[0],ftr[1],ftr[2]);
    glVertex3f(fbr[0],fbr[1],fbr[2]);
    
    glEnd();
}


void Frustum::drawPlanes() {
    
    glBegin(GL_QUADS);
    
    //near plane
    glVertex3f(ntl[0],ntl[1],ntl[2]);
    glVertex3f(ntr[0],ntr[1],ntr[2]);
    glVertex3f(nbr[0],nbr[1],nbr[2]);
    glVertex3f(nbl[0],nbl[1],nbl[2]);
    
    //far plane
    glVertex3f(ftr[0],ftr[1],ftr[2]);
    glVertex3f(ftl[0],ftl[1],ftl[2]);
    glVertex3f(fbl[0],fbl[1],fbl[2]);
    glVertex3f(fbr[0],fbr[1],fbr[2]);
    
    //bottom plane
    glVertex3f(nbl[0],nbl[1],nbl[2]);
    glVertex3f(nbr[0],nbr[1],nbr[2]);
    glVertex3f(fbr[0],fbr[1],fbr[2]);
    glVertex3f(fbl[0],fbl[1],fbl[2]);
    
    //top plane
    glVertex3f(ntr[0],ntr[1],ntr[2]);
    glVertex3f(ntl[0],ntl[1],ntl[2]);
    glVertex3f(ftl[0],ftl[1],ftl[2]);
    glVertex3f(ftr[0],ftr[1],ftr[2]);
    
    //left plane
    
    glVertex3f(ntl[0],ntl[1],ntl[2]);
    glVertex3f(nbl[0],nbl[1],nbl[2]);
    glVertex3f(fbl[0],fbl[1],fbl[2]);
    glVertex3f(ftl[0],ftl[1],ftl[2]);
    
    // right plane
    glVertex3f(nbr[0],nbr[1],nbr[2]);
    glVertex3f(ntr[0],ntr[1],ntr[2]);
    glVertex3f(ftr[0],ftr[1],ftr[2]);
    glVertex3f(fbr[0],fbr[1],fbr[2]);
    
    glEnd();

}



void Frustum::update(Camera c, float nearDist, float farDist, float fov, float ratio){
    
    
    this->ratio = ratio;
    this->angle = fov*HALF_ANG2RAD;
    this->nearD = nearDist;
    this->farD = farDist;
    this->tang = tan(this->angle);
    
    sphereFactorY = 1.0/cos(this->angle);//tang * sin(this->angle) + cos(this->angle);
    
    float anglex = atan(tang*ratio);
    sphereFactorX = 1.0/cos(anglex);
   
    nh = nearD * tang;
    nw = nh * ratio;
    fh = farD  * tang;
    fw = fh * ratio;

}

void Frustum::drawNormals(){
    Vector3 a,b;
    
    glBegin(GL_LINES);
    
    // near
    a = (ntr + ntl + nbr + nbl) * 0.25;
    b = a + pl[NEARP].normal;
    glVertex3f(a[0],a[1],a[2]);
    glVertex3f(b[0],b[1],b[2]);
    
    // far
    a = (ftr + ftl + fbr + fbl) * 0.25;
    b = a + pl[FARP].normal;
    glVertex3f(a[0],a[1],a[2]);
    glVertex3f(b[0],b[1],b[2]);
    
    // left
    a = (ftl + fbl + nbl + ntl) * 0.25;
    b = a + pl[LEFT].normal;
    glVertex3f(a[0],a[1],a[2]);
    glVertex3f(b[0],b[1],b[2]);
    
    // right
    a = (ftr + nbr + fbr + ntr) * 0.25;
    b = a + pl[RIGHT].normal;
    glVertex3f(a[0],a[1],a[2]);
    glVertex3f(b[0],b[1],b[2]);
    
    // top
    a = (ftr + ftl + ntr + ntl) * 0.25;
    b = a + pl[TOP].normal;
    glVertex3f(a[0],a[1],a[2]);
    glVertex3f(b[0],b[1],b[2]);
    
    // bottom
    a = (fbr + fbl + nbr + nbl) * 0.25;
    b = a + pl[BOTTOM].normal;
    glVertex3f(a[0],a[1],a[2]);
    glVertex3f(b[0],b[1],b[2]);
    
    glEnd();

}
void Frustum::display(){
    drawPoints();
    drawLines();
    drawPlanes();
    drawNormals();
}
void Frustum::setCamDef(Vector3 p, Vector3 l, Vector3 u){
    Vector3 dir,nc,fc;
    this->camPos = p;
    
    this->Z = p - l;
    this->Z.normalizeThis();
    
    this->X = u.cross(Z);
    X.normalizeThis();
    
    this->Y = Z.cross(X);
    //Y.normalizeThis();
    
    nc = p - Z * nearD;
    fc = p - Z * farD;
    
    ntl = nc + Y * nh - X * nw;
    ntr = nc + Y * nh + X * nw;
    nbl = nc - Y * nh - X * nw;
    nbr = nc - Y * nh + X * nw;
    
    // compute the 4 corners of the frustum on the far plane
    ftl = fc + Y * fh - X * fw;
    fbr = fc - Y * fh + X * fw;
    ftr = fc + Y * fh + X * fw;
    fbl = fc - Y * fh - X * fw;
    
    
    pl[TOP].set3Points(ntr, ntl, ftl);
    pl[BOTTOM].set3Points(nbl, nbr, fbr);
    pl[LEFT].set3Points(ntl, nbl, fbl);
    pl[RIGHT].set3Points(nbr, ntr, fbr);
    
    //pl[NEARP].set3Points(ntl, ntr, nbr);
    // pl[FARP].set3Points(ftr, ftl, fbl);
    
    pl[NEARP].setNormalAndPoint(Z*-1,nc);
    pl[FARP].setNormalAndPoint(Z,fc);
 
    Vector3 aux,normal;
    
    aux = (nc + Y*nh) - p;
    normal = aux.cross(X);
    pl[TOP].setNormalAndPoint(normal,nc+Y*nh);
    
    aux = (nc - Y*nh) - p;
    normal = X.cross(aux);
    pl[BOTTOM].setNormalAndPoint(normal,nc-Y*nh);
    
    aux = (nc - X*nw) - p;
    normal = aux.cross( Y);
    pl[LEFT].setNormalAndPoint(normal,nc-X*nw);
    
    aux = (nc + X*nw) - p;
    normal = Y.cross( aux);
    pl[RIGHT].setNormalAndPoint(normal,nc+X*nw);
    
}



int Frustum::contains(BoundingShpere sub,Matrix4 m){
   
    Vector3 p = (m*sub.coordinates).toVector3();
    
   // float radius = .3*sub.radius;
     float radius = .3*sub.radius;
    float d1,d2;
    float az,ax,ay,zz1,zz2;
    int result = INSIDE;
    
    Vector3 v = p-camPos;
    //v.print("fuk\n");
   // std::cout<<"RADIUS "<<radius<<std::endl;
    az = v.dot(Z*-1);
    if (az > farD + radius || az < nearD-radius){
      //  std::cout<<"heren0\n";
        return(OUTSIDE);
    }
    
    ax = v.dot(X);
    zz1 = az * tang * ratio;
    d1 = sphereFactorX * radius;
    if (ax > zz1+d1 || ax < -zz1-d1){
        // std::cout<<"heren1\n";
        return(OUTSIDE);
    }
    
    ay = v.dot(Y);
    zz2 = az * tang;
    d2 = sphereFactorY * radius;
    if (ay > zz2+d2 || ay < -zz2-d2){
      //  std::cout<<"heren2\n";
        return(OUTSIDE);
    }
    if (az > farD - radius || az < nearD+radius){
        result = INTERSECT;
    }
    if (ay > zz2-d2 || ay < -zz2+d2){
        result = INTERSECT;
    }
    if (ax > zz1-d1 || ax < -zz1+d1){
        result = INTERSECT;
    }
    
   // std::cout<<"Result "<<result<<" Outside "<<OUTSIDE<<std::endl;
    return(result);


    
}