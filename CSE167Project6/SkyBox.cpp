//
//  SkyBox.cpp
//  CSE167 Spring 2015 Starter Code
//
//  Created by Victor Alor on 11/8/15.
//  Copyright © 2015 RexWest. All rights reserved.
//
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <math.h>
#include "SkyBox.hpp"
SkyBox::SkyBox(){

}
void SkyBox::init(){
    front  = Texture("darkskies_ft.ppm");
    back  = Texture("darkskies_bk.ppm");
    down = Texture("darkskies_dn.ppm");
    up = Texture("darkskies_up.ppm");
    left = Texture("darkskies_rt.ppm");
    right = Texture("darkskies_lf.ppm");
    Matrix4 fuckThis;
   // fuckThis.makeRotateY(45*M_PI/180);
    toWorld.identity();
    //toWorld = fuckThis*toWorld;
}

void SkyBox::draw(){
    float halfSize = 400/ 2.0;
    
    glMatrixMode(GL_MODELVIEW);
    
    //Push a save state onto the matrix stack, and multiply in the toWorld matrix
    glPushMatrix();
    glMultMatrixf(toWorld.ptr());
  
    back.bind();
    
    glBegin(GL_QUADS);
      glColor3f(1, 1, 1);
    
    glNormal3f(0.0, 0.0, 1.0);
    glTexCoord2f(1, 0); glVertex3f(-halfSize, halfSize, halfSize);
    glTexCoord2f(0, 0); glVertex3f(halfSize, halfSize, halfSize);
    glTexCoord2f(0, 1); glVertex3f(halfSize, -halfSize, halfSize);
    glTexCoord2f(1, 1); glVertex3f(-halfSize, -halfSize, halfSize);
    
    
    glEnd();
    back.unbind();
    
 
    up.bind();
    glBegin(GL_QUADS);
      glColor3f(1, 1, 1);
    glNormal3f(0, 1.0, 0.0);
    glTexCoord2f(0,0 );glVertex3f( halfSize,  halfSize,  halfSize);
    glTexCoord2f(0,1 );glVertex3f(-halfSize,  halfSize,  halfSize);
    glTexCoord2f(1,1 ); glVertex3f(-halfSize,  halfSize, -halfSize);
    glTexCoord2f(1, 0);glVertex3f( halfSize,  halfSize, -halfSize);
  
    glEnd();
    
    up.unbind();
    
    down.bind();
     glBegin(GL_QUADS);
      glColor3f(1, 1, 1);
    glNormal3f(0, -1.0, 0.0);
     glTexCoord2f(1,1 ); glVertex3f(halfSize, -halfSize, -halfSize);
    glTexCoord2f(1,0 ); glVertex3f(-halfSize, -halfSize, -halfSize);
   
    glTexCoord2f(0,0 ); glVertex3f(-halfSize, -halfSize, halfSize);
    glTexCoord2f(0, 1); glVertex3f(halfSize, -halfSize, halfSize);
    glEnd();
    down.unbind();
    
    left.bind();
    
    glBegin(GL_QUADS);
      glColor3f(1, 1, 1);
    glNormal3f(-1.0, 0.0, 0.0);
     glTexCoord2f(1,0 ); glVertex3f(-halfSize, halfSize, -halfSize);
    glTexCoord2f(0,0 ); glVertex3f(-halfSize, halfSize, halfSize);
   glTexCoord2f(0, 1); glVertex3f(-halfSize, -halfSize, halfSize);
    glTexCoord2f(1,1 ); glVertex3f(-halfSize, -halfSize, -halfSize);
    

    glEnd();
    left.unbind();
    //std::cerr<<left.id<<std::endl;
       // Draw right
    right.bind();
    glBegin(GL_QUADS);
      glColor3f(1, 1, 1);
    glNormal3f(1.0, 0.0, 0.0);
    glTexCoord2f(1,0 ); glVertex3f(halfSize, halfSize, halfSize);
    glTexCoord2f(0,0 ); glVertex3f(halfSize, halfSize, -halfSize);
    glTexCoord2f(0,1 ); glVertex3f(halfSize, -halfSize, -halfSize);
    glTexCoord2f(1, 1); glVertex3f(halfSize, -halfSize, halfSize);
    glEnd();
    right.unbind();
   
    
    front.bind();
    glBegin(GL_QUADS);
      glColor3f(1, 1, 1);
    // Draw front face:
    glNormal3f(0.0, 0.0, -1.0);
    
    glTexCoord2f(0, 1); glVertex3f(-halfSize, -halfSize, -halfSize);
    glTexCoord2f(1, 1); glVertex3f(halfSize, -halfSize, -halfSize);
    glTexCoord2f(1, 0); glVertex3f(halfSize, halfSize, -halfSize);
    glTexCoord2f(0, 0); glVertex3f(-halfSize, halfSize, -halfSize);
    glEnd();
    front.unbind();
    
    //This will undo the multiply we did earlier
    glPopMatrix();
    
}