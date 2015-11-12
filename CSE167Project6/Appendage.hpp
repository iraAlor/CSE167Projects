//
//  Appendage.hpp
//  CSE167 Spring 2015 Starter Code
//
//  Created by Victor Alor on 11/1/15.
//  Copyright © 2015 RexWest. All rights reserved.
//

#ifndef Appendage_hpp
#define Appendage_hpp

#include <stdio.h>
#include "MatrixTransform.hpp"
#include <list>
#include <math.h>

class Appendage : public MatrixTransform{
    
private:
    float angle;
    float delta;
    
public:
    Appendage(float angle);
    void update();
    
};
#endif /* Appendage_hpp */
