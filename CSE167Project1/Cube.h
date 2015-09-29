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
    
    virtual void draw(DrawData&);
    virtual void update(UpdateData&);
    
    void spin(float);
    void trans(float,float,float);
    void reset(void);
    void rotate(float);
    float rotRate;
    void scale(float);
    void printCoord(void);
};

#endif

