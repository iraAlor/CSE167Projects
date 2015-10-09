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
 int frame=0,tme,timebase=0;

void Window::initialize(void)
{
    //Setup the light
    Vector4 lightPos(0.0, 10.0, 15.0, 1.0);
    Globals::light.position = lightPos;
    Globals::light.quadraticAttenuation = 0.02;
    Globals::updateData.w = width;
    Globals::updateData.h = height;
    Globals::updateData.z = 10;
    //Initialize cube matrix:10.0
    Drawable * sub = new Cube(10.0);
    Color color(0x23ff27ff);
    sub->material.color = color;
    Globals::man.addToMode(0,sub);
    sub = new Sphere(3.0,100,100);
    sub->material.color = color;
    Globals::man.addToMode(3,sub);
    

    Globals::house = House();
    Globals::house.toWorld.identity();
   
   
}

//----------------------------------------------------------------------------
// Callback method called when system is idle.
// This is called at the start of every new "frame" (qualitatively)
void Window::idleCallback()
{
    //Set up a static time delta for update calls
    Globals::updateData.dt = 1.0/60.0;// 60 fps
    Globals::updateData.w = width/2;
    Globals::updateData.h = height/2;
    Globals::updateData.z = width/2;
    
    //Rotate cube; if it spins too fast try smaller values and vice versa
    if(Globals::project %2 == 0){
       
       Globals::man.changeOne(&Drawable::spin,0.005);
       Globals::man.updateStuff(Globals::updateData);
       
    }
   
    frame++;
    tme=glutGet(GLUT_ELAPSED_TIME);
    if (tme - timebase > 1000) {
        std::cout<<frame*1000.0/(tme-timebase)<<std::endl;
        timebase = tme;
        frame = 0;
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
    if(Globals::project %2 ==0){
    
       Globals::man.drawStuff(Globals::drawData);
    }
    else{
        
        Globals::house.draw();
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
void Window::nonCamMode(int key, int x,int y){
    if(Globals::project %2!=0){
        return;
    }
    switch (key) {
        case 'c':
            Globals::man.changeZero(&Drawable::toggleSpin);
            break;
        case 'x':
            Globals::man.changeThree((&Drawable::trans),-1.0,0,0);
            break;
        case 'X':
            Globals::man.changeThree((&Drawable::trans),1.0,0,0);
            break;
        case 'Y':
            Globals::man.changeThree((&Drawable::trans),0,1,0);
            break;
        case 'y':
            Globals::man.changeThree((&Drawable::trans),0,-1,0);
            break;
        case 'z':
            Globals::man.changeThree((&Drawable::trans),0,0,-1.0);
            break;
        case 'Z':
            Globals::man.changeThree((&Drawable::trans),0,0,1);
            break;
        case 'r':
            Globals::man.reset();
            break;
        case 'o':
            Globals::man.changeOne((&Drawable::rotate),1.0);
            break;
        case 'O':
            Globals::man.changeOne((&Drawable::rotate),-1.0);
            break;
        case  's':
            Globals::man.changeOne((&Drawable::scale),.90);
            break;
        case 'S':
            Globals::cube.scale(1.10);
            Globals::man.changeOne((&Drawable::scale),1.10);
            break;
        case 'b':
            if(Globals::man.getMode()!=3){
                Globals::man.setMode(3);
            }
            else{
                Globals::man.reset();
                Globals::man.setMode(0);
                
            }
            break;
        default:
            break;
    }
    Globals::man.changeZero((&Drawable::printCoord));
    
}
void Window::camMode(int key, int x, int y){
    if(Globals::project %2!=0){
        return;
    }
    switch (key) {
        case 'x':
            Globals::camera.changePos(0, -.5);
            break;
        case 'X':
            Globals::camera.changePos(0, .5);
            break;
        case 'Y':
            Globals::camera.changePos(1, -.5);
            break;
        case 'y':
           Globals::camera.changePos(1, .5);
            break;
        case 'z':
            Globals::camera.changePos(2,-.5);
            break;
        case 'Z':
            Globals::camera.changePos(2,.5);
            break;
        case 'r':
            Globals::camera.reset();
            break;
        case 'u':
            Globals::camera.invert();
            break;
        case 'w':
            Globals::camera.move(1,.5);
            break;
        case 's':
            Globals::camera.move(1,-.5);
            break;
        case 'a':
            Globals::camera.move(0,-.5);
            break;
        case 'd':
            Globals::camera.move(0,.5);
            break;
        case 'f':
            Globals::camera.move(2,.5);
            break;
        case 'F':
            Globals::camera.move(2,-.5);
            break;
        case 'Q':
            Globals::camera.tilt(0.0872665);
            break;
        case 'q':
            Globals::camera.tilt(-0.0872665);
            break;
        default:
            break;
    }

}
void Window::processKeys(unsigned char key,int x,int y){
   
    if(Globals::mode){
        nonCamMode(key,x,y);
    }
    else{
        camMode(key,x,y);
    }
  
    

}
void Window::multiMode(int key,int x,int y){
    std::cout<<"here\n";
    switch(key){
        case GLUT_KEY_F4:
            Globals::man.addToMode(8,"bear.obj");
            //Globals::man.changeZero(&Drawable::printCoord);
            break;
            
        case GLUT_KEY_F5:
            Globals::man.addToMode(8,"bunny.obj");
            break;
        case GLUT_KEY_F6:
            Globals::man.addToMode(8,"dragon.obj");
            break;
        case GLUT_KEY_F7:
            Globals::mode = !Globals::mode;
            break;
        case GLUT_KEY_F8:
            Globals::multi = !Globals::multi;
          
            break;
    }
}
void Window::processSpecKeys(int key,int x,int y){
    Vector3 e;
    Vector3 d;
    Vector3 up;
     //F4, F5 and F6
    if(Globals::multi){
        multiMode(key, x, y);
        return;
    }
    switch(key){
        case GLUT_KEY_F1:
            if(Globals::project != 0){
                Globals::man.setMode(0);
            }
            else{
                //Globals::man.addToMode(0,new Cube(10.0));
            }
            Globals::project = 0;
            
            break;
        case GLUT_KEY_F2:
            Globals::project = 1;
            e =Vector3(0,24.14,24.14);
            d =Vector3(0,0,0);
            up =Vector3(0,1,0);
            Globals::camera.set(e,d,up);
            break;
        case GLUT_KEY_F3:
            e =Vector3(-28.33,11.66,23.33);
            d =Vector3(-5,0,0);
            up =Vector3(0,1,.5);
            Globals::camera.set(e,d,up);
            Globals::project = 1;
            break;
        case GLUT_KEY_F4:
            
            if(Globals::project != 2){
                Globals::man.setMode(2,"bear.obj");
            }
            else{
               // Globals::man.addToMode(2,"bear.obj");
            }
            Globals::man.changeZero(&Drawable::printCoord);
            Globals::project = 2;
            
            break;
            
        case GLUT_KEY_F5:
            if(Globals::project != 4){
                Globals::man.setMode(4,"bunny.obj");
            }
            else{
             //   Globals::man.addToMode(4,"bunny.obj");
            }
            Globals::project = 4;
            break;
        case GLUT_KEY_F6:
            if(Globals::project != 6){
                //Globals::man.setMode(6);
                Globals::man.setMode(6,"dragon.obj");
            }
            else{
           //     Globals::man.addToMode(6,"dragon.obj");
            }
            Globals::project = 6;
            break;
        case GLUT_KEY_F7:
            Globals::mode = !Globals::mode;
            break;
        case GLUT_KEY_F8:
            Globals::multi = !Globals::multi;
            Globals::man.multiMode();
            break;
            
            
    }
    if(Globals::project %2 == 0){
        glEnable(GL_LIGHTING);
        Globals::camera.reset();
    }
    
    
}
//TODO: Keyboard callbacks!

//TODO: Function Key callbacks!

//TODO: Mouse callbacks!

//TODO: Mouse Motion callbacks!
