//
//  BezyCurve.cpp
//  CSE167 Spring 2015 Starter Code
//
//  Created by Victor Alor on 11/8/15.
//  Copyright © 2015 RexWest. All rights reserved.
//

#include "BezyCurve.hpp"
#include "Vector4.h"
#include "Vector3.h"
#include <vector>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <cmath>
#include "Material.h"
BezyCurve::BezyCurve(Matrix4 x,Matrix4 y,Matrix4 z,int level){
    bezyMat.set(-1,3,-3,1,
                 3,-6,3,0,
                -3,3,0,0 ,
                1,0,0,0);
    x0 = x;
    y0 = y;
    z0 = z;
    bezyX = bezyMat*x*bezyMat;
    bezyY = bezyMat*y*bezyMat;
    bezyZ = bezyMat*z*bezyMat;
    this->level = level;
    toWorld.identity();
    tex=0;
    mode = false;
    dt = 1/60.0;
    time = 0.0;
}

void BezyCurve::setSecond(Matrix4 x, Matrix4 y, Matrix4 z){
    mode = true;
    bezyX1 = bezyMat*x*bezyMat;
    bezyY1 = bezyMat*y*bezyMat;
    bezyZ1 = bezyMat*z*bezyMat;
    x1 = x;
    y1 = y;
    z1 = z;

}

Vector3 BezyCurve::calcPoint(float u, float v){
    Vector4 uvec = Vector4(u*u*u, u*u, u, 1);
    Vector4 vvec = Vector4(v*v*v,v*v,v,1);
    float x = uvec.dot(bezyX*vvec);
    float y=uvec.dot(bezyY*vvec);
    float z=uvec.dot(bezyZ*vvec);
    return Vector3(x,y,z);
}


Vector3 BezyCurve::calcPoint2(float u, float v){
    Vector4 uvec = Vector4(u*u*u, u*u, u, 1);
    Vector4 vvec = Vector4(v*v*v,v*v,v,1);
    float x = uvec.dot(bezyX1*vvec);
    float y=uvec.dot(bezyY1*vvec);
    float z=uvec.dot(bezyZ1*vvec);
    return Vector3(x,y,z);
}

Vector3 BezyCurve::calcNormal2(float u, float v){
    Vector4 uvec = Vector4(u*u*u, u*u, u, 1);
    Vector4 vvec = Vector4(v*v*v,v*v,v,1);
    Vector4 duvec = Vector4(3*u*u,2*u,1,0);
    Vector4 dvvec = Vector4(2*v*v,2*v,1,0);
    float x0 = uvec.dot(bezyX1*dvvec);
    float y0 = uvec.dot(bezyY1*dvvec);
    float z0 = uvec.dot(bezyZ1*dvvec);
    float x1 = duvec.dot(bezyX1*vvec);
    float y1 = duvec.dot(bezyY1*vvec);
    float z1 = duvec.dot(bezyZ1*vvec);
    return Vector3(x1,y1,z1).cross(Vector3(x0, y0, z0));
}

Vector3 BezyCurve::calcNormal(float u, float v){
    Vector4 uvec = Vector4(u*u*u, u*u, u, 1);
    Vector4 vvec = Vector4(v*v*v,v*v,v,1);
    Vector4 duvec = Vector4(3*u*u,2*u,1,0);
    Vector4 dvvec = Vector4(2*v*v,2*v,1,0);
    float x0 = uvec.dot(bezyX*dvvec);
    float y0 = uvec.dot(bezyY*dvvec);
    float z0 = uvec.dot(bezyZ*dvvec);
    float x1 = duvec.dot(bezyX*vvec);
    float y1 = duvec.dot(bezyY*vvec);
    float z1 = duvec.dot(bezyZ*vvec);
    return Vector3(x1,y1,z1).cross(Vector3(x0, y0, z0));
}
void BezyCurve::drawTwo(){
    glMatrixMode(GL_MODELVIEW);
    float lev = (float) level;
    //Push a save state onto the matrix stack, and multiply in the toWorld matrix
    glPushMatrix();
    glMultMatrixf(toWorld.ptr());
    
    tex->bind();
    glBegin(GL_QUADS);
    Vector4 top;
    Vector4 bott;
    glColor3f(1.0, 1.0, 1.0);
    int i = 0;
    for(i = 0;i<level;i++){
        bool first = true;
        Vector3 a = calcPoint(0, (i + 1)/lev);
        top[0] = 0;
        top[1] = (i + 1)/lev;
        Vector3 b = calcPoint(0,i/lev);
        top[2] = 0;
        top[3] = i/lev;
        for(int j = 1;j<=level;j++){
            Vector3  c = calcPoint(j/lev, i/lev);
            Vector3  d = calcPoint(j/lev, (i + 1)/lev);
            bott[0] = j/lev;
            bott[1] = i/lev;
            bott[2] = j/lev;
            bott[3] = (i+1)/lev;
            
            Vector3 an = calcNormal(top[0],top[1]).normalize();
            Vector3 bn = calcNormal(top[2], top[3]).normalize();
            Vector3 cn = calcNormal(bott[0], bott[1]).normalize();
            Vector3 dn = calcNormal(bott[2], bott[3]).normalize();
     
            glNormal3f(dn[0], dn[1], dn[2]);
            glTexCoord2f(bott[0], bott[1]);
            glVertex3f(d[0], d[1], d[2]);
            
            glNormal3f(cn[0], cn[1], cn[2]);
            glTexCoord2f(bott[0], bott[1]);
            glVertex3f(c[0], c[1], c[2]);
            
            glNormal3f(bn[0], bn[1], bn[2]);
            glTexCoord2f(top[2], top[3]);
            glVertex3f(b[0], b[1], b[2]);
            
            glNormal3f(an[0], an[1], an[2]);
            glTexCoord2f(top[0], top[1]);
            glVertex3f(a[0], a[1], a[2]);
            
            
            
            a = d;
            b = c;
            top = bott;
            first = false;
            
            
        }
        
    }
    for(int i = 0;i<level;i++){
        bool first = true;
        Vector3 a = calcPoint2(0, (i + 1)/lev);
        top[0] = 0;
        top[1] = (i + 1)/lev;
        Vector3 b = calcPoint2(0,i/lev);
        top[2] = 0;
        top[3] = i/lev;
        for(int j = 1;j<=level;j++){
            Vector3  c = calcPoint2(j/lev, i/lev);
            Vector3  d = calcPoint2(j/lev, (i + 1)/lev);
            bott[0] = j/lev;
            bott[1] = i/lev;
            bott[2] = j/lev;
            bott[3] = (i+1)/lev;
            
            Vector3 an = calcNormal2(top[0],top[1]).normalize();
            Vector3 bn = calcNormal2(top[2], top[3]).normalize();
            Vector3 cn = calcNormal2(bott[0], bott[1]).normalize();
            Vector3 dn = calcNormal2(bott[2], bott[3]).normalize();
      
            glNormal3f(dn[0], dn[1], dn[2]);
            glTexCoord2f(bott[0], bott[1]);
            glVertex3f(d[0], d[1], d[2]);
            
            glNormal3f(cn[0], cn[1], cn[2]);
            glTexCoord2f(bott[0], bott[1]);
            glVertex3f(c[0], c[1], c[2]);
            
            glNormal3f(bn[0], bn[1], bn[2]);
            glTexCoord2f(top[2], top[3]);
            glVertex3f(b[0], b[1], b[2]);
            
            glNormal3f(an[0], an[1], an[2]);
            glTexCoord2f(top[0], top[1]);
            glVertex3f(a[0], a[1], a[2]);
            
            
            
            a = d;
            b = c;
            top = bott;
            first = false;
            
            
        }
        
    }
    
    glEnd();
    /*
     bl.print("0,0");
     br.print("1,0");
     tr.print("1,1");
     tl.print("0,1");
     */
    tex->unbind();
    glPopMatrix();

}

void BezyCurve::drawOne(){
    
    glMatrixMode(GL_MODELVIEW);
    float lev = (float) level;
    //Push a save state onto the matrix stack, and multiply in the toWorld matrix
    glPushMatrix();
    glMultMatrixf(toWorld.ptr());
    
    tex->bind();
    glBegin(GL_QUADS);
    Vector4 top;
    Vector4 bott;
    float off = sinf(time);
    glColor3f(1.0, 1.0, 1.0);
    for(int i = 0;i<level;i++){
        bool first = true;
        Vector3 a = calcPoint(0, (i + 1)/lev);
        top[0] = 0;
        top[1] = (i + 1)/lev;
        Vector3 b = calcPoint(0,i/lev);
        top[2] = 0;
        top[3] = i/lev;
        for(int j = 1;j<=level;j++){
            Vector3  c = calcPoint(j/lev, i/lev);
            Vector3  d = calcPoint(j/lev, (i + 1)/lev);
            bott[0] = j/lev;
            bott[1] = i/lev;
            bott[2] = j/lev;
            bott[3] = (i+1)/lev;
            
            Vector3 an = calcNormal(top[0],top[1]).normalize();
            Vector3 bn = calcNormal(top[2], top[3]).normalize();
            Vector3 cn = calcNormal(bott[0], bott[1]).normalize();
            Vector3 dn = calcNormal(bott[2], bott[3]).normalize();
            
   
            glNormal3f(dn[0], dn[1], dn[2]);
            glTexCoord2f(bott[0], bott[1]);
            glVertex3f(d[0], d[1], d[2]);
            
            glNormal3f(cn[0], cn[1], cn[2]);
            glTexCoord2f(bott[0], bott[1]);
            glVertex3f(c[0], c[1], c[2]);
            
            glNormal3f(bn[0], bn[1], bn[2]);
            glTexCoord2f(top[2], top[3]);
            glVertex3f(b[0], b[1], b[2]);
            
            glNormal3f(an[0], an[1], an[2]);
            glTexCoord2f(top[0], top[1]);
            glVertex3f(a[0], a[1], a[2]);
            
            
            
            a = d;
            b = c;
            top = bott;
            first = false;
            
            
        }
        
    }
    
    
    glEnd();
    /*
     bl.print("0,0");
     br.print("1,0");
     tr.print("1,1");
     tl.print("0,1");
     */
    tex->unbind();
    glPopMatrix();

}
void BezyCurve::init(){
    if(!mode){
    drawOne();
    }
    else{
        drawTwo();
    }
}
void BezyCurve::render(){
     Material notRed = Material(Color::white(), Color::white(), Color::white(), Color::white(), Color::white(), 0);
    notRed.apply();
    for(int i = 0;i<100;i++){
        glBegin(GL_QUADS);
        glVertex3f(quads[0][0][0], quads[0][0][1], quads[0][0][2]);
        glVertex3f(quads[0][1][0], quads[0][1][1], quads[0][1][2]);
        glVertex3f(quads[0][2][0], quads[0][2][1], quads[0][2][2]);
        glVertex3f(quads[0][3][0], quads[0][3][1], quads[0][3][2]);
        glEnd();
    }
}
void BezyCurve::update(){
    
    time+=dt;
    float delta = sinf(time);
    float delta2 = cosf(time)*sinf(time);
    float delta3 = sinf(time);
    if(time>=.3|| time<=-.2){
        dt*=-1;
    }
    if(dt<0){
        delta*=-1;
        delta2*=-1;
        delta3*=-1;
    }
    
    for(int i = 1;i<2;i++){
        for(int j = 0;j<4;j++){
            x0.set(i,j,x0.get(i,j)+delta);
            y0.set(i,j, y0.get(i,j)+delta);
            z0.set(i,j, z0.get(i,j)+delta);
        }
    }
    for(int i = 2;i<4;i++){
        for(int j = 0;j<4;j++){
            x0.set(i,j,x0.get(i,j)+delta2);
            y0.set(i,j, y0.get(i,j)+delta2);
            z0.set(i,j, z0.get(i,j)+delta2);
        }
    }
    for(int i = 0;i<2;i++){
        for(int j = 0;j<4;j++){
            x1.set(i,j, x1.get(i,j)+delta2);
            y1.set(i,j, y1.get(i,j)+delta2);
            z1.set(i,j, z1.get(i,j)+delta2);
        }
    }
    for(int i = 2;i<4;i++){
        for(int j = 0;j<4;j++){
            x1.set(i,j,x1.get(i,j)+delta3);
            y1.set(i,j, y1.get(i,j)+delta3);
            z1.set(i,j, z1.get(i,j)+delta3);
        }
    }
    bezyX = bezyMat*x0*bezyMat;
    bezyY = bezyMat*y0*bezyMat;
    bezyZ = bezyMat*z0*bezyMat;
    
    bezyX1 = bezyMat*x1*bezyMat;
    bezyY1 = bezyMat*y1*bezyMat;
    bezyZ1 = bezyMat*z1*bezyMat;
    
    

    
}