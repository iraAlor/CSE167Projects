#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#ifdef __APPLE__
     #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

#include "Window.h"

#include "Matrix4.h"
#include "Globals.h"
#include "MathTestBench.h"

static int window_width = 512, window_height = 512;
int main(int argc, char *argv[])
{
    //Math Test Bench
    MathTestBench::runTests();
   
    //GLUT and OpenGL Configuration
    glutInit(&argc, argv);                                      //Initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);   //Open an OpenGL context with double buffering, RGB colors, and depth buffering
    glutInitWindowSize(Window::width, Window::height);          //Set initial window size

    Globals::main_window = glutCreateWindow("CSE 167 Project 3");
    
   // srand (time(NULL));
    Globals::port.update(window_width,window_height);
    Globals::projection.update(60.0, double(window_width)/(double)window_height, 1.0, 1000.0);
    Globals::pixels.update(window_width, window_height);
    //Globals::frustum.update(Globals::camera, 1, 1000, 60.0, double(window_width)/(double)window_height);
    //Globals::frustum.setCamDef(Globals::camera.e, Globals::camera.d,  Globals::camera.up);
    
    glEnable(GL_DEPTH_TEST);                                    //Enable depth buffering
    glClear(GL_DEPTH_BUFFER_BIT);                               //Clear depth buffer
    glClearColor(0.0, 0.0, 0.0, 0.0);                           //Set clear color to black
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);                  //Set polygon drawing mode to fill front and back of each polygon
    glDisable(GL_CULL_FACE);                                    //Disable backface culling to render both sides of polygons
    glShadeModel(GL_SMOOTH);                                    //Set shading to smooth
    
    //glEnable(GL_COLOR_MATERIAL);                                //Enable color materials
    glEnable(GL_LIGHTING);                                      //Enable lighting
    glEnable(GL_NORMALIZE);                                     //Auto normalize surface normals
    glEnable(GL_TEXTURE_2D);                                    //Enable 2D textures
    glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);        //Enable Local Viewer Light Model
    
    //glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
   
    //Register callback functions:
    glutDisplayFunc(Window::displayCallback);
    glutReshapeFunc(Window::reshapeCallback);
    glutIdleFunc(Window::idleCallback);
    //Register the callback for the keyboard
    //Register the callback for the keyboard function keys
    //Register the callback for the mouse
    //Register the callback for the mouse motion
    //Register the callback for the mouse passive motion
    glutKeyboardFunc(Window::processKeys);
    glutSpecialFunc(Window::processSpecKeys);
    
   
    
    glutMouseFunc(Window::processMousePress);
    glutMotionFunc(Window::processMouseMove);
    //Print Shader Debug Information:
    printf("%s\n%s\n",
           glGetString(GL_RENDERER),  // e.g. Intel HD Graphics 3000 OpenGL Engine
           glGetString(GL_VERSION)    // e.g. 3.2 INTEL-8.0.61
           );
    std::printf("Supported GLSL version is %s.\n", (char *)glGetString(GL_SHADING_LANGUAGE_VERSION));
    
    //Initialize the Window:
    //The body of this function is a great place to load textures, shaders, etc.
    //and do any operations/calculations/configurations that only need to happen once.
    Globals::mode = true;
    Globals::project  = 0;
    Window::initialize();
   
    //Start up the render loop!
    glutMainLoop();
    
    return 0;
}
