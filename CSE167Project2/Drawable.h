#ifndef CSE167_Drawable_h
#define CSE167_Drawable_h

#include <iostream>
#include "Matrix4.h"
#include "DrawData.h"
#include "UpdateData.h"
#include "Material.h"
#include <float.h>
#include <math.h>
#include <vector>


class Drawable
{
    
public:
    
    Matrix4 toWorld;
    Material material;
    
    Drawable(void);
    ~Drawable(void);
    
    virtual void draw(DrawData&);
    virtual void update(UpdateData&);
    virtual void spin(float );
    virtual void trans(float,float,float );
    virtual void reset();
    virtual void rotate(float);
    virtual void scale(float sFactor);
    virtual void printCoord();
    virtual void toggleSpin();
    
};

#endif