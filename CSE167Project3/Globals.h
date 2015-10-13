#ifndef CSE167_Globals_h
#define CSE167_Globals_h

#include "Camera.h"
#include "Cube.h"
#include "Light.h"
#include "DrawData.h"
#include "UpdateData.h"
#include "Sphere.h"
#include "House.h"
#include "OBJObjectMan.hpp"
#include "ViewPort.hpp"
#include "Projection.hpp"
#include "Canvas.hpp"
class Globals
{
    
public:
    static unsigned int project;
    static Camera camera;
    static Cube cube;
    static Sphere sphere;
    static bool mode;
    static Light light;
    static DrawData drawData;
    static UpdateData updateData;
    static House house;
    static OBJObjectMan man;
    static bool multi;
    static ViewPort port;
    static bool engine;
    static Projection projection;
    static Canvas pixels;

    //Feel free to add more member variables as needed
    
};


#endif
