#include "Drawable.h"
#include "Window.h"

Drawable::Drawable()
{
    this->toWorld.identity();
}

Drawable::~Drawable()
{
    //
}

void Drawable::draw(DrawData& data)
{
    std::cout << "Warning: draw() is not implemented" << std::endl;
}

void Drawable::update(UpdateData& data)
{
    std::cout << "Warning: update() is not implemented" << std::endl;
}
void Drawable::printCoord(){
    toWorld.printCol(3);
}

void Drawable::trans(float x,float y,float z){}
void Drawable::spin(float r){};
void Drawable::reset(){
    toWorld.identity();
}
void Drawable::rotate(float x){}
void Drawable::scale(float a){}
void Drawable::toggleSpin(){}