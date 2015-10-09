//
//  House.h
//  CSE167 Spring 2015 Starter Code
//
//  Created by Victor Alor on 10/5/15.
//  Copyright © 2015 RexWest. All rights reserved.
//

#ifndef House_h
#define House_h
#include <vector>

#include "Drawable.h"
class House : public Drawable{
private:
    std::vector<float> farr;
    std::vector<float> carr;
    std::vector<int> inds;
public:
    
House(std::vector<float> farr,std::vector<float> carr,std::vector<int> indices);
House();
void draw();
};

#endif /* House_h */
