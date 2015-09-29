#include "Globals.h"

Camera Globals::camera;
bool Globals::mode = true;
Cube Globals::cube(10.0);
Sphere Globals::sphere(3.0,100,100);
Light Globals::light;

DrawData Globals::drawData;
UpdateData Globals::updateData;