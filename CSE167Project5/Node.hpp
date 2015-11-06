//
//  Node.hpp
//  CSE167 Spring 2015 Starter Code
//
//  Created by Victor Alor on 10/31/15.
//  Copyright © 2015 RexWest. All rights reserved.
//

#ifndef Node_hpp
#define Node_hpp
#include "Matrix4.h"
#include "BoundingSphere.hpp"
#include "Globals.h"
#include <stdio.h>

class Node{
protected:
    Node * parent;
    std::string name;
   
    bool collision = false;
public:
    BoundingShpere boundingSphere;
    virtual void draw(Matrix4 C) = 0;
    virtual void update() = 0;
 
    
};
#endif /* Node_hpp */
