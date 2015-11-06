//
//  MatrixTransform.cpp
//  CSE167 Spring 2015 Starter Code
//
//  Created by Victor Alor on 10/31/15.
//  Copyright © 2015 RexWest. All rights reserved.
//

#include "MatrixTransform.hpp"
MatrixTransform::MatrixTransform(){
    transform.identity();
}
Matrix4 MatrixTransform::getTform(){
    return transform;
}
void MatrixTransform::setTform(Matrix4 t){
    transform = t;
}

MatrixTransform::MatrixTransform(Matrix4 t){
    transform = t;
}

void MatrixTransform::draw(Matrix4 c){
    Matrix4 c_new = c*transform;
    for(auto it =  children.begin();it!=children.end();it++){
        (*it)->draw(c_new);
    }
}