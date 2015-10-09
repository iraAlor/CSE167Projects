//
//  House.cpp
//  CSE167 Spring 2015 Starter Code
//
//  Created by Victor Alor on 10/5/15.
//  Copyright © 2015 RexWest. All rights reserved.
//


#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdio.h>
#include "House.h"
#include <iostream>
static float vertices[] = {
    -4,-4,4, 4,-4,4, 4,4,4, -4,4,4,     // front face
    -4,-4,-4, -4,-4,4, -4,4,4, -4,4,-4, // left face
    4,-4,-4,-4,-4,-4, -4,4,-4, 4,4,-4,  // back face
    4,-4,4, 4,-4,-4, 4,4,-4, 4,4,4,     // right face
    4,4,4, 4,4,-4, -4,4,-4, -4,4,4,     // top face
    -4,-4,4, -4,-4,-4, 4,-4,-4, 4,-4,4, // bottom face
    
    -20,-4,20, 20,-4,20, 20,-4,-20, -20,-4,-20, // grass
    -4,4,4, 4,4,4, 0,8,4,                       // front attic wall
    4,4,4, 4,4,-4, 0,8,-4, 0,8,4,               // left slope
    -4,4,4, 0,8,4, 0,8,-4, -4,4,-4,             // right slope
    4,4,-4, -4,4,-4, 0,8,-4};                   // rear attic wall
static int indices[] = {
    0,2,3,    0,1,2,      // front face
    4,6,7,    4,5,6,      // left face
    8,10,11,  8,9,10,     // back face
    12,14,15, 12,13,14,   // right face
    16,18,19, 16,17,18,   // top face
    20,22,23, 20,21,22,   // bottom face
    
    24,26,27, 24,25,26,   // grass 42
    28,29,30,             // front attic wall 45
    31,33,34, 31,32,33,   // left slope 51
    35,37,38, 35,36,37,   // right slope 57
    39,40,41};            // rear attic wall 60
static float colors[] = {
    1,0,0, 1,0,0, 1,0,0, 1,0,0,  // front is red
    0,1,0, 0,1,0, 0,1,0, 0,1,0,  // left is green
    1,0,0, 1,0,0, 1,0,0, 1,0,0,  // back is red
    0,1,0, 0,1,0, 0,1,0, 0,1,0,  // right is green
    0,0,1, 0,0,1, 0,0,1, 0,0,1,  // top is blue
    0,0,1, 0,0,1, 0,0,1, 0,0,1,  // bottom is blue
    
    0,0.5,0, 0,0.5,0, 0,0.5,0, 0,0.5,0, // grass is dark green
    0,0,1, 0,0,1, 0,0,1,                // front attic wall is blue
    1,0,0, 1,0,0, 1,0,0, 1,0,0,         // left slope is green
    0,1,0, 0,1,0, 0,1,0, 0,1,0,         // right slope is red
    0,0,1, 0,0,1, 0,0,1,};


void House::draw(){
   glMatrixMode(GL_MODELVIEW);
   glPushMatrix();
   glMultMatrixf(toWorld.ptr());
    material.apply();
    glDisable(GL_LIGHTING);
   glBegin(GL_TRIANGLES);

    
    int index;
    for (int i = 0; i < 60; i++){
        index = indices[i];

        glColor3f(colors[3 * index], colors[3 * index + 1], colors[3 * index + 2]);
        glVertex3f(vertices[3 * index], vertices[3 * index + 1], vertices[3 * index + 2]);
    }
    glEnd();
   glPopMatrix();
}
House::House(std::vector<float> a,std::vector<float> b,std::vector<int> c){
    farr = a;
    carr = b;
    inds = c;
}
House::House(){
    
    // This data structure defines a simple house
    
   
}