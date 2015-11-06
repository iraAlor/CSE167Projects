//
//  ViewPort.cpp
//  CSE167 Spring 2015 Starter Code
//
//  Created by Victor Alor on 10/11/15.
//  Copyright © 2015 RexWest. All rights reserved.
//

#include "ViewPort.hpp"
ViewPort::ViewPort(float x0,float x1,float y0,float y1){
    this->update(x0,x1, y0, y1);
}
ViewPort::ViewPort(float x,float y){
    ViewPort(0,x,0,y);
}
ViewPort::ViewPort(){
    port.identity();
}
void ViewPort::update(float x0,float x1,float y0,float y1){
    port.set((x1-x0)/2.0,0.0,0.0,0.0,
             0.0,(y1-y0)/2.0,0.0,0.0,
             0.0,0.0,1.0/2.0,0.0,
             (x1-x0)/2.0,(y1-y0)/2.0,1.0/2.0,1.0);
  
    
}
void ViewPort::update(float x, float y){
    this->update(0, x, 0, y);
}
Matrix4& ViewPort::getMatrix(){
    return port;
}