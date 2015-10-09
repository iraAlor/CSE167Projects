#ifndef CSE167_Cube_h
#define CSE167_Cube_h

#include "Drawable.h"

class Cube : public Drawable
{

public:
    
    float size;
    int spinDir;
    Cube(float);
    virtual ~Cube(void);
    Matrix4 orbit;
    
    virtual void draw(DrawData&);
    virtual void update(UpdateData&);
    
    virtual void spin(float);
    virtual void trans(float,float,float);
    virtual void reset(void);
    virtual void rotate(float);
    float rotRate;
    virtual void scale(float);
    virtual void printCoord(void);
    virtual void toggleSpin();
};

#endif

