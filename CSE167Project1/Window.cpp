#include <iostream>

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

#include "Window.h"
#include "Cube.h"
#include "Matrix4.h"
#include "Globals.h"

int Window::width  = 512;   //Set window width in pixels here
int Window::height = 512;   //Set window height in pixels here


void Window::initialize(void)
{
    //Setup the light
    Vector4 lightPos(0.0, 10.0, 15.0, 1.0);
    Globals::light.position = lightPos;
    Globals::light.quadraticAttenuation = 0.02;
    Globals::updateData.w = width;
    Globals::updateData.h = height;
    Globals::updateData.z = 10;
    //Initialize cube matrix:
    Globals::cube.toWorld.identity();
    Globals::sphere.toWorld.identity();
    
    //Setup the cube's material properties
    Color color(0x23ff27ff);
    Globals::cube.material.color = color;
}

//----------------------------------------------------------------------------
// Callback method called when system is idle.
// This is called at the start of every new "frame" (qualitatively)
void Window::idleCallback()
{
    //Set up a static time delta for update calls
    Globals::updateData.dt = 1.0/60.0;// 60 fps
    
    //Rotate cube; if it spins too fast try smaller values and vice versa
    if(Globals::mode){
       Globals::cube.spin(0.005);
       //Call the update function on cube
       Globals::cube.update(Globals::updateData);
    }
    else{
        Globals::updateData.w = width/2;
        Globals::updateData.h = height/2;
        Globals::updateData.z = width/2;
        Globals::sphere.update(Globals::updateData);
    }
    
    
    //Call the display routine to draw the cube
    displayCallback();
}

//----------------------------------------------------------------------------
// Callback method called by GLUT when graphics window is resized by the user
void Window::reshapeCallback(int w, int h)
{
    width = w;                                                       //Set the window width
    height = h;                                                      //Set the window height
    glViewport(0, 0, w, h);                                          //Set new viewport size
    glMatrixMode(GL_PROJECTION);                                     //Set the OpenGL matrix mode to Projection
    glLoadIdentity();                                                //Clear the projection matrix by loading the identity
    gluPerspective(60.0, double(width)/(double)height, 1.0, 1000.0); //Set perspective projection viewing frustum
}

//----------------------------------------------------------------------------
// Callback method called by GLUT when window readraw is necessary or when glutPostRedisplay() was called.
void Window::displayCallback()
{
    //Clear color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    //Set the OpenGL matrix mode to ModelView
    glMatrixMode(GL_MODELVIEW);
    
    //Push a matrix save point
    //This will save a copy of the current matrix so that we can
    //make changes to it and 'pop' those changes off later.
    glPushMatrix();
    
    //Replace the current top of the matrix stack with the inverse camera matrix
    //This will convert all world coordiantes into camera coordiantes
    glLoadMatrixf(Globals::camera.getInverseMatrix().ptr());
    
    //Bind the light to slot 0.  We do this after the camera matrix is loaded so that
    //the light position will be treated as world coordiantes
    //(if we didn't the light would move with the camera, why is that?)
    Globals::light.bind(0);
    
    //Draw the cube!
    if (Globals::mode){
        Globals::cube.draw(Globals::drawData);
    }
    else{
        Globals::sphere.draw(Globals::drawData);
    }
    
    //Pop off the changes we made to the matrix stack this frame
    glPopMatrix();
    
    
    //Tell OpenGL to clear any outstanding commands in its command buffer
    //This will make sure that all of our commands are fully executed before
    //we swap buffers and show the user the freshly drawn frame
    glFlush();
    
    //Swap the off-screen buffer (the one we just drew to) with the on-screen buffer
    glutSwapBuffers();
}

void Window::processKeys(unsigned char key,int x,int y){
   
    switch (key) {
        case 't':
            Globals::cube.spinDir *= -1;
            break;
        case 'x':
            Globals::cube.trans(-1.0,0,0);
            break;
        case 'X':
            Globals::cube.trans(1.0,0,0);
            break;
        case 'Y':
            Globals::cube.trans(0,1.0,0);
            break;
        case 'y':
            Globals::cube.trans(0.0,-1.0,0);
            break;
            
        case 'z':
            Globals::cube.trans(0.0,0.0,-1.0);
            break;
            
        case 'Z':
            Globals::cube.trans(0.0,0.0,1.0);
            break;
        case 'r':
            Globals::cube.reset();
            break;
        case 'o':
            Globals::cube.rotate(-1.0);
            break;
        case 'O':
            Globals::cube.rotate(1.0);
            break;
        case  's':
            Globals::cube.scale(.90);
            break;
        case 'S':
            Globals::cube.scale(1.10);
            break;
        case 'b':
            Globals::mode = !Globals::mode;
            Globals::sphere.reset();
            
            break;
        default:
            break;
    }
    if(Globals::mode){
      Globals::cube.printCoord();
    }


}
//TODO: Keyboard callbacks!

//TODO: Function Key callbacks!

//TODO: Mouse callbacks!

//TODO: Mouse Motion callbacks!
