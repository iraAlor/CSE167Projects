//
//  Rasterizer.cpp
//  CSE167 Spring 2015 Starter Code
//
//  Created by Victor Alor on 10/10/15.
//  Copyright © 2015 RexWest. All rights reserved.
//

#include <stdio.h>
#ifdef _WIN32
#include <windows.h>
#endif
#ifdef __APPLE__
#include <GLUT/glut.h>

#else
#include <GL/glut.h>
#include <GL/gl.h>
#endif

#include <iostream>
#include <math.h>



static int window_width = 512, window_height = 512;
static float* pixels = new float[window_width * window_height * 3];

using namespace std;

struct Color    // generic color
{
    float r,g,b;
};

void loadData()
{
    // put code to load data model here
}

// Clear frame buffer
void clearBuffer()
{
    Color clearColor = {0.0, 0.0, 0.0};   // clear color: black
    for (int i=0; i<window_width*window_height; ++i)
    {
        pixels[i*3]   = clearColor.r;
        pixels[i*3+1] = clearColor.g;
        pixels[i*3+2] = clearColor.b;
    }
}

// Draw a point into the frame buffer
void drawPoint(int x, int y, float r, float g, float b)
{
    int offset = y*window_width*3 + x*3;
    pixels[offset]   = r;
    pixels[offset+1] = g;
    pixels[offset+2] = b;
}

void rasterizeTriangle()
{
    // Add code to rasterize a triangle
}

void rasterize()
{
    // Put your main rasterization loop here
    // It should go over the data model and call rasterizeTriangle for every triangle in it
    
    // example: draw diagonal line:
    for (int i=0; i<min(window_width,window_height); ++i)
    {
        drawPoint(i, i, 1.0, 0.0, 0.0);
    }
}

// Called whenever the window size changes
void reshape(int new_width, int new_height)
{
    window_width  = new_width;
    window_height = new_height;
    delete[] pixels;
    pixels = new float[window_width * window_height * 3];
}

void keyboard(unsigned char key, int, int)
{
    cerr << "Key pressed: " << key << endl;
}

void display()
{
    clearBuffer();
    rasterize();
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // glDrawPixels writes a block of pixels to the framebuffer
    glDrawPixels(window_width, window_height, GL_RGB, GL_FLOAT, pixels);
    
    glutSwapBuffers();
}

int tempt(int argc, char** argv) {
    glutInit(&argc, argv);
    
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(window_width, window_height);
    glutCreateWindow("CSE 167 Project 3");
   
    loadData();
    
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glutMainLoop();
    return 0;
}