#include "Globals.h"

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