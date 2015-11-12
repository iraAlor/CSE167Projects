#ifndef CSE167_Window_h
#define CSE167_Window_h
#include "Vector3.h"
class Window	  // OpenGL output window related routines
{
    
public:
    
    static int width, height; 	            // window size
    static void nonCamMode(int key,int x,int y);
    static void camMode(int key,int x,int y);
    static void initialize(void);
    static void idleCallback(void);
    static void reshapeCallback(int, int);
    static void displayCallback(void);
    static void processKeys(unsigned char,int,int);
    static void processSpecKeys(int key,int x,int y);
    static void multiMode(int key,int x,int y);
    static void updateEngine(bool);
    static void updateFrustum();
    static void processMousePress(int button,int state,int x,int y);
    static void processMouseMove(int x,int y);
    static Vector3 trackBallMapping(double x,double y);
    static void detectCollision();
    static void detectCollision2();
};

#endif

