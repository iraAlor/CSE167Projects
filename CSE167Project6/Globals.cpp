#include "Globals.h"
static Matrix4 xMatrix = Matrix4(-10,-10,-10,-10,
                                 -5,-5,-5,-5,
                                 0,0,0,0,
                                 5,5,5,5);
static Matrix4 yMatrix = Matrix4(-10,-5,0,5,
                                 -10,-5,0,5,
                                 -10,-5,0,5,
                                 -10,-5,0,5);
static Matrix4 zMatrix = Matrix4(5,5,5,5,
                                 1,1,1,1,
                                 5,5,5,5,
                                 -1,-1,-1,-1);
static Matrix4 x2Matrix = Matrix4(5,5,5,5,
                           10,10,10,10,
                           15,15,15,15,
                           17,17,17,17);
static Matrix4 y2Matrix = Matrix4(-10,-5,0,5,
                                  -10,-5,0,5,
                                  -10,-5,0,5,
                                  -10,-5,0,5);
static Matrix4 z2Matrix = Matrix4(-1,-1,-1,-1,
                                 -5,-5,-5,-5,
                                 5,5,5,5,
                                 -1,-1,-1,-1);

Camera Globals::camera;
bool Globals::mode = true;
Light Globals::light;
unsigned int Globals::project = 0;
DrawData Globals::drawData;
UpdateData Globals::updateData;
House Globals::house;
OBJObjectMan Globals::man;
bool Globals::multi = false;
ViewPort Globals::port;
Projection Globals::projection;
bool Globals::engine = true;
Canvas Globals::pixels;
int Globals::main_window = 0;
bool Globals::bsMode = false;
bool Globals::cullMode = false;
Frustum Globals::frustum;
std::list<BoundingShpere *> Globals::g1 = {};
std::list<std::list<BoundingShpere *>> Globals::g2 = {};
std::list<BoundingShpere *> Globals::temp = {};
bool Globals::marchMode = false;
bool Globals::controlMode = false;
Matrix4 Globals::rotation1;
Matrix4 Globals::rotation2;
float Globals::otherCounter = 0;
SkyBox Globals::skyBox;
BezyCurve Globals::bCurve(xMatrix,yMatrix,zMatrix,300);
Texture Globals::flag;
Shader * Globals::shader;
