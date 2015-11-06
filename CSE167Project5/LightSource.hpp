//
//  LightSource.hpp
//  CSE167 Spring 2015 Starter Code
//
//  Created by Victor Alor on 10/14/15.
//  Copyright © 2015 RexWest. All rights reserved.
//

#ifndef LightSource_hpp
#define LightSource_hpp

#include <stdio.h>
#include "Vector3.h"
class LightSource{
    
private:
    
    Vector3 color;
public:
    
    LightSource();
    LightSource(float x,float y,float z);
    LightSource(float x,float y,float z,float r,float g,float b);
    Vector3 coord;
    Vector3 getL(Vector3 destination);
    Vector3 getC(Vector3 destination);

    
    
    
    
    
    
};

#endif /* LightSource_hpp */
