#include <iostream>

#ifdef __APPLE__
    #include <GLUT/glut.h>
    #include <GL/glui.h>
#else
    #include <GL/glut.h>
#endif

#include "Window.h"

#include "Matrix4.h"
#include "Globals.h"
#include "Robot.hpp"
#include "Geode.hpp"
#include "Platoon.hpp"
#include "General.hpp"
#include "General2.hpp"
int Window::width  = 512;   //Set window width in pixels here
int Window::height = 512;   //Set window height in pixels here
 int frame=0,tme,timebase=0;
Vector3 lastPoint;
static Light someOther;
static MatrixTransform * scaly;
static Robot * robo;
static Platoon * plat;
static Platoon * plat2;
static General * gen;
static General2 * gen2;
int mouseMode;
Light * lSub = 0;
bool guiMode = false;
static DirectionalLight dLight = DirectionalLight(0,0,1,Color::black(),Color::white(),Color::white());
static PointLight pLight =   PointLight(12,0,0,Color::black(),Color::white(),Color::white());
static SpotLight sLight = SpotLight(0,12,0,Color::black(),Color::white(),Color::white());
GLfloat objectXform[4][4] =
{
    {1.0, 0.0, 0.0, 0.0},
    {0.0, 1.0, 0.0, 0.0},
    {0.0, 0.0, 1.0, 0.0},
    {0.0, 0.0, 0.0, 1.0}
};
void Window::updateFrustum(){
    
    Globals::frustum.update(Globals::camera, 1, 1000, 60.0, double(width)/(double)height);
    Globals::frustum.setCamDef(Globals::camera.e, Globals::camera.d,  Globals::camera.up);
    
}
void Window::initialize(void)
{
    //Setup the light
    Vector4 lightPos(0.0, 10.0, 10.0, 1.0);
    Globals::light.position = lightPos;
    Globals::light.quadraticAttenuation = 0.00;
    
    
    lightPos = Vector4(-5,10,10,1.0);
    someOther.position =lightPos;
    
    Globals::updateData.w = width;
    Globals::updateData.h = height;
    Globals::updateData.z = 10;;
    robo = new Robot(4,4);
    Matrix4 temp;
    scaly = new MatrixTransform(temp.makeScale(.3));
   // scaly->addChild(robo);
    Globals::bsMode = false;
    plat = new Platoon(14,3,robo,-80);
    plat2 = new Platoon(14,3,robo,80);
  //  plat = new Platoon(1,1,robo,-60);
   /// plat2 = new Platoon(1,1,robo,60);
    gen = new General();
    plat->dir = 0;
    plat->mode =Platoon::TRANSLEFT;
    plat2->dir =1;
    plat2->rot.makeRotateY(-M_PI/2.0);
    plat2->mode = Platoon::TRANSRIGHT;
    gen2 = new General2();

    gen->addChild(plat);
    gen2->addChild(plat2);
 
    scaly->addChild(gen);
    scaly->addChild(gen2);
    updateFrustum();
   // Globals::frustum.printPlanes();
   
    mouseMode = -1;
    
    
   
   
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

   
    frame++;
    tme=glutGet(GLUT_ELAPSED_TIME);
    if (tme - timebase > 1000) {
        std::cout<<"FPS:"<<frame*1000.0/(tme-timebase)<<std::endl;
        timebase = tme;
        frame = 0;
       
    }

   robo->update();
    //Call the display routine to draw the cube
   displayCallback();
}

//----------------------------------------------------------------------------
// Callback method called by GLUT when graphics window is resized by the user
void Window::reshapeCallback(int w, int h)
{
    width = w;                                                       //Set the window width
    
    height = h;                                                      //Set the window height
   
      glViewport(0, 0, w, h);  //Set new viewport size
        
      glMatrixMode(GL_PROJECTION);                                     //Set the OpenGL matrix mode to Projection
      glLoadIdentity();                                                //Clear the projection matrix by loading the identity
      gluPerspective(60.0, double(width)/(double)height, 1.0, 1000.0);
      updateFrustum();

}
void Window::detectCollision(){
    if(!Globals::bsMode){
        return;
    }
    Material red = Material(Color(0.05f, 0.f, 0.f, 1.f), Color(0.5f, 0.4f, 0.4f, 1.f), Color(0.7f, 0.04f, 0.04f, 1.f), Color::emissionMaterialDefault(), Color::red(), 10.f);
    Material notRed = Material(Color::white(), Color::white(), Color::white(), Color::white(), Color::white(), 0);
    //std::cout<<"det\n";
    for(auto it0 = Globals::g1.begin();it0!=Globals::g1.end();it0++){
        Material  mat = notRed;
        //std::cout<<"det0\n";
        for(auto it = Globals::g1.begin();it!=Globals::g1.end();it++){
            if(*it0 == *it){
                continue;
            }
            Vector3 subCoord = (*it0)->tempCoord.toVector3();
            Vector3 otherCoord = (*it)->tempCoord.toVector3();
            float dist = (subCoord-otherCoord).magnitude();
            float rad = (.6*(*it0)->radius);
      //      if(subCoord[2]==0 && otherCoord[2]==0){
        //    subCoord.print("c1");
          //  otherCoord.print("c2");
           // std::cout<<"det0 "<<rad<<" dist "<<dist<<std::endl;
           // }
           
            if(dist<=rad){
             //   subCoord.print("c1");
               // otherCoord.print("c2");
              //std::cout<<"det0 "<<rad<<" dist "<<dist<<std::endl;

              mat = red;
            }
            
        }
        (*it0)->mat = mat;
        (*it0)->display();
    }
   for(auto it0 = Globals::g1.begin();it0!=Globals::g1.end();it0++){
        //delete *it0;
    }
   // exit(0);
}


void Window::detectCollision2(){
    if(!Globals::bsMode){
        return;
    }
    Material red = Material(Color(0.05f, 0.f, 0.f, 1.f), Color(0.5f, 0.4f, 0.4f, 1.f), Color(0.7f, 0.04f, 0.04f, 1.f), Color::emissionMaterialDefault(), Color::red(), 10.f);
    Material notRed = Material(Color::white(), Color::white(), Color::white(), Color::white(), Color::white(), 0);
    //std::cout<<"det\n";
    for(auto it0 = Globals::g2.begin();it0!=Globals::g2.end();it0++){
       // Material  mat = notRed;
        //std::cout<<"det0\n";
        for(auto it = Globals::g2.begin();it!=Globals::g2.end();it++){
            if(*it0 == *it){
                continue;
            }
         
            
            for(auto it1 = it0->begin();it1!=it0->end();it1++){
                Material  mat = notRed;
                for(auto it2 = it->begin();it2!=it->end();it2++){
                    if(*it1==*it2){
                        continue;
                    }
                    Vector3 subCoord = (*it1)->tempCoord.toVector3();
                    Vector3 otherCoord = (*it2)->tempCoord.toVector3();
                    float dist = (subCoord-otherCoord).magnitude();
                    float rad = 5*((*it1)->radius);
                     std::cout<<dist<<" "<< rad<<std::endl;
                    if(dist<=rad){
                        //   subCoord.print("c1");
                        // otherCoord.print("c2");
                        //std::cout<<"det0 "<<rad<<" dist "<<dist<<std::endl;
                        
                        mat = red;
                }
                (*it1)->mat = mat;
                (*it1)->display();
                
            }
            
            }
            
            
        }
    }
    for(auto it0 = Globals::g2.begin();it0!=Globals::g2.end();it0++){
        for(auto it1 = it0->begin();it1!=it0->end();it1++){
          // delete *it1;
        }
    }
    // exit(0);
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
    someOther.bind(1);
     // Globals::frustum.display();
     //Draw the cube!
    Matrix4 seed;

    seed.identity();
    //plat->draw(seed);
   scaly->draw(seed);
    //robo->draw(seed);
     Globals::otherCounter+=-24.0/100.0;
     scaly->update();
   
    detectCollision();
     Globals::g1 = {};
   // detectCollision2();
   // Globals::g2  = {};
    //Globals::temp = {};
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
    //std::cout<<"h=red "<<Globals::project<<std::endl;
   
    
}
void Window::camMode(int key, int x, int y){
   

}
void Window::updateEngine(bool en){
    if(en){
        Globals::port.update(width,height);
        Globals::projection.update(60.0, double(width)/(double)height, 1.0, 1000.0);
        Globals::pixels.update(width, height);
    }
    else{
        glViewport(0, 0, width, height);  //Set new viewport size
        glMatrixMode(GL_PROJECTION);                                     //Set the OpenGL matrix mode to Projection
        glLoadIdentity();                                                //Clear the projection matrix by loading the identity
        gluPerspective(60.0, double(width)/(double)height, 1.0, 1000.0);
    }
}
void Window::processKeys(unsigned char key,int x,int y){
    switch (key) {
        case 'b':
            Globals::bsMode=!Globals::bsMode;
            //std::cout<<"here\n";
            break;
        case 'c':
            Globals::cullMode=!Globals::cullMode;
            break;
        case 'x':
            Globals::camera.rotateX(1.0*M_PI/(180.0));
            updateFrustum();
            break;
        case 'X':
            Globals::camera.rotateX(-1.0*M_PI/(180.0));
            updateFrustum();
            break;
        case 'y':
            Globals::camera.rotateY(1.0*M_PI/(180.0));
            updateFrustum();
            break;
        case 'Y':
             Globals::camera.rotateY(-1.0*M_PI/(180.0));
            updateFrustum();
            break;
        case 'z':
            Globals::camera.rotateZ(1.0*M_PI/(180.0));
            updateFrustum();
            break;
        case 'Z':
            Globals::camera.rotateZ(-1.0*M_PI/(180.0));
            updateFrustum();
            break;
        case 's':
            Globals::camera.scale(1.10);
            updateFrustum();
            break;
        case 'S':
            Globals::camera.scale(.9);
            updateFrustum();
            break;
        case 'r':
            Globals::camera.reset();
            updateFrustum();
            break;
        case 'm':
            Globals::marchMode = !Globals::marchMode ;
            Globals::controlMode = false;
            plat->reset();
            plat2->reset();
            gen->reset();
            gen2->reset();
            scaly->update();
            break;
        case 'n':
            Globals::controlMode = !Globals::controlMode;
            Globals::marchMode = false;
            plat->reset();
            plat2->reset();
            gen->reset();
            gen2->reset();
            scaly->update();
            break;
        case 'o':
            gen->move(0,-1);
            plat->setRotation(0);
            break;
        case 'O':
            gen->move(0,1);
            plat->setRotation(2);
            break;
        case 'p':
            gen->move(2,1);
            plat->setRotation(3);
            break;
        case 'P':
            gen->move(2,-1);
            plat->setRotation(1);
            break;
        case 'u':
            gen2->move(0,-1);
             plat2->setRotation(0);
            break;
        case 'U':
             gen2->move(0,1);
            plat2->setRotation(2);
            break;
        case 'i':
            gen2->move(2,1);
             plat2->setRotation(3);
            break;
        case 'I':
            gen2->move(2,-1);
            plat2->setRotation(1);
            break;
        default:
            break;
    }

}
void Window::multiMode(int key,int x,int y){
   
}
void Window::processSpecKeys(int key,int x,int y){
   
    
}
Vector3 Window::trackBallMapping(double x, double y){
    Vector3 res;
    float d;
    res[0] = (2.0*x-(float)Window::width)/(float)Window::width;
    res[1] =((float)Window::height-2.0*y)/(float)Window::height;
    res[2] = 0.0;
    d = res.magnitude();
    d = (d<1.0) ? d : 1.0;
    res[2] = sqrtf(1.001 - d*d);
    res.normalizeThis();
    return res;
}


void Window::processMouseMove(int x, int y){
  
    
}
void Window::processMousePress(int button,int state,int x,int y){
    mouseMode = -1;
    // std::cout<<button<<" "<<state<<std::endl;
    if(state == GLUT_UP){
        mouseMode = -1;
    }
    
    mouseMode = button == GLUT_LEFT_BUTTON ? 1:2;
    if(glutGetModifiers()==GLUT_ACTIVE_SHIFT){
        mouseMode = 3;
    }
    lastPoint = trackBallMapping(x, y);

}


 

//TODO: Keyboard callbacks!

//TODO: Function Key callbacks!

//TODO: Mouse callbacks!

//TODO: Mouse Motion callbacks!
