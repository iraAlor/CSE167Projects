#ifndef CSE167_OBJObject_h
#define CSE167_OBJObject_h

#include <iostream>
#include <vector>
#include <string>
#include "Vector3.h"
#include "Drawable.h"
#include <limits>
struct Face
{
    int vertexIndices[3];
    int normalIndices[3];
    int textureIndices[3];
    //Add more members as necessary
};

class OBJObject : public Drawable
{
    
protected:
    
    //Storage vectors
    std::vector<Vector3*>* vertices;
    std::vector<Vector3*>* normals;
  //  std::vector<Face*>* faces;
    std::vector<Vector3*>* colors;
    
    //Helper functions
    std::vector<std::string>& split(const std::string&, char, std::vector<std::string>&);
    std::vector<std::string> split(const std::string&, char);
    Vector3 centerCoordsMax;
    Vector3 centerCoordsMin;
    Vector3 halfSize;
    Vector3 scaleVector;
    float centerx;
    float centery;
    float centerz;
    Matrix4 scaleMat;
    //Parse
    void parse(std::string&);
    float factor;
   
    
public:
     int spinDir;
    std::vector<Face*>* faces;
    OBJObject(std::string);
    virtual ~OBJObject(void);
    OBJObject(OBJObject *);
    OBJObject();
    virtual std::vector<Vector3*> * getVert();
    virtual void draw(DrawData&);
    virtual void update(UpdateData&);
    virtual void spin(float );
    virtual void trans(float,float,float );
    virtual void reset();
    virtual void rotate(float);
    virtual void scale(float sFactor);
    virtual void printCoord();
    virtual void toggleSpin();
    virtual std::vector<Vector3*>* getNorms();
    virtual void scaleToWindow(double factor);
    
    
};

#endif
