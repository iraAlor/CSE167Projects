#include "Globals.h"

Camera Globals::camera;
bool Globals::mode = true;
Cube Globals::cube(10.0);
Sphere Globals::sphere(3.0,100,100);
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

