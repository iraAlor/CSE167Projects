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
 //   MathTestBench::runTests();
   
    //GLUT and OpenGL Configuration
    glutInit(&argc, argv);                                      //Initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);   //Open an OpenGL context with double buffering, RGB colors, and depth buffering
    glutInitWindowSize(Window::width, Window::height);          //Set initial window size

    Globals::main_window = glutCreateWindow("CSE 167 Project 6");
    /*
    
    glEnable(GL_TEXTURE_2D);                                    //Enable 2D textures
    glShadeModel(GL_SMOOTH);                                    //Set shading to smooth
    // glClearColor(0.0, 0.0, 0.0, 0.0);                           //Set clear color to black
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);                                    //Enable depth buffering
    glDepthFunc(GL_LEQUAL);
   // glClear(GL_DEPTH_BUFFER_BIT);                               //Clear depth buffer
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);          // really nice perspective calculations
   
   
  
  //  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);                  //Set polygon drawing mode to fill front and back of each polygon
   // glDisable(GL_CULL_FACE);                                    //Disable backface culling to render both sides of polygons
  
    
    glEnable(GL_COLOR_MATERIAL);                                //Enable color materials
   // glEnable(GL_LIGHTING);                                      //Enable lighting
   // glEnable(GL_NORMALIZE);                                     //Auto normalize surface normals
    
    glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);        //Enable Local Viewer Light Model
    
    
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    */
    //glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
    
    glEnable(GL_DEPTH_TEST);                                    //Enable depth buffering
    glClear(GL_DEPTH_BUFFER_BIT);                               //Clear depth buffer
    glClearColor(0.0, 0.0, 0.0, 0.0);                           //Set clear color to black
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);                  //Set polygon drawing mode to fill front and back of each polygon
    glDisable(GL_CULL_FACE);                                    //Disable backface culling to render both sides of polygons
    glShadeModel(GL_SMOOTH);                                    //Set shading to smooth
    glEnable(GL_TEXTURE_2D);
    
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glEnable(GL_COLOR_MATERIAL);                                //Enable color materials
    glEnable(GL_LIGHTING);                                      //Enable lighting
     glEnable(GL_NORMALIZE);
    
    glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   
    
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
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
   
    Globals::skyBox.init();
    Globals::flag = Texture("Ucsd-logo2.ppm");
    Window::initialize();
    Shader shader = Shader("vertexShader", "FragmentShader");
   // shader.bind();
    Globals::shader = & shader;
    Globals::shader->bind();
    Globals::shader->unbind();
    //Start up the render loop!
    glutMainLoop();
    
    return 0;
}

