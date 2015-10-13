#ifndef CSE167_Window_h
#define CSE167_Window_h

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
};

#endif

