#ifndef CSE167_Globals_h
#define CSE167_Globals_h

#include "Camera.h"

#include "Light.h"
#include "PointLight.hpp"
#include "SpotLight.hpp"
#include "DirectionalLight.hpp"
#include "DrawData.h"
#include "UpdateData.h"

#include "House.h"
#include "OBJObjectMan.hpp"
#include "ViewPort.hpp"
#include "Projection.hpp"
#include "Canvas.hpp"
#include "Frustum.hpp"
#include "Texture.h"
#include <list>
#include "SkyBox.hpp"
#include "BezyCurve.hpp"
#include "Shader.h"
class Globals
{
    
public:
    static unsigned int project;
    static Camera camera;
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
    static int main_window;
    static bool bsMode;
    static Frustum frustum;
    static bool cullMode;
    static std::list<BoundingShpere *> g1;
    static bool marchMode;
    static bool controlMode;
    static Matrix4 rotation1;
    static Matrix4 rotation2;
    static float otherCounter;
    static std::list<std::list<BoundingShpere *>> g2;
    static std::list<BoundingShpere *> temp;
    static SkyBox skyBox;
    static BezyCurve bCurve;
    static Texture flag;
    static Shader * shader;
    //Feel free to add more member variables as needed
    
};


#endif
