//
//  SkyBox.hpp
//  CSE167 Spring 2015 Starter Code
//
//  Created by Victor Alor on 11/8/15.
//  Copyright © 2015 RexWest. All rights reserved.
//

#ifndef SkyBox_hpp
#define SkyBox_hpp

#include <stdio.h>
#include "Texture.h"
#include "Matrix4.h"
class SkyBox{
public:
    Texture front;
    Texture back;
    Texture up;
    Texture down;
    Texture right;
    Texture left;
    SkyBox();
    void draw();
    void init();
    Matrix4 toWorld;
};
#endif /* SkyBox_hpp */
