#ifndef CSE167_Light_h
#define CSE167_Light_h

#include "Matrix4.h"
#include "Vector4.h"
#include "Color.h"
#include <iostream>
#include "Vector3.h"
#include <vector>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
class Light
{
    
protected:
    
    int bindID = -1;
    
public:
    
    Vector4 position;
    Color ambientColor;
    Color diffuseColor;
    Color specularColor;
    
    float constantAttenuation;
    float linearAttenuation;
    float quadraticAttenuation;
    
public:
    
    Light();
    virtual ~Light(void);
    
    virtual void bind(int);
    virtual void unbind(void);
    virtual void rotateLight(Matrix4 rot){};
    virtual void scaleLight(float dir){};
    virtual void changeExp(float dir){};
    virtual void changeFOV(float dir){};
};

#endif
