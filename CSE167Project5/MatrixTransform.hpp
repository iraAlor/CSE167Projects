//
//  MatrixTransform.hpp
//  CSE167 Spring 2015 Starter Code
//
//  Created by Victor Alor on 10/31/15.
//  Copyright © 2015 RexWest. All rights reserved.
//

#ifndef MatrixTransform_hpp
#define MatrixTransform_hpp

#include <stdio.h>
#include "Node.hpp"
#include "Group.hpp"
class MatrixTransform :public Group{
protected:
    Matrix4 transform;
    
public:
    Matrix4 getTform();
    void setTform(Matrix4 t);
    MatrixTransform();
    MatrixTransform(Matrix4 t);
    void draw(Matrix4 m);
   
};
#endif /* MatrixTransform_hpp */
