//
//  OBJObjectMan.hpp
//  CSE167 Spring 2015 Starter Code
//
//  Created by Victor Alor on 10/6/15.
//  Copyright © 2015 RexWest. All rights reserved.
//

#ifndef OBJObjectMan_hpp
#define OBJObjectMan_hpp

#include <stdio.h>
#include "OBJObject.h"
#include <unordered_map>
#include <string>
#include <vector>

class OBJObjectMan{
    
private:
    std::unordered_map<std::string,OBJObject*> mapy;
    std::unordered_map<int,std::vector <Drawable*>*> dmap;
    int mode;
    int oldMode;
public:
  
    OBJObjectMan();
    ~OBJObjectMan();
    OBJObject * getObject(std::string);
    void setMode(int);
    void drawStuff(DrawData&);
    void updateStuff(UpdateData&);
    void addDrawMode(int );
    void addToMode(int,Drawable *);
    void addToMode(int ,std::string);
    void setMode(int,std::string);
    void reset();
    void changeZero(void (Drawable::*pntrName)());
    void changeOne(void (Drawable::*pntrName)(float),float);
    void changeThree(void (Drawable::*pntrName)(float,float,float),float,float,float);
    int getMode(){return mode;}
    void multiMode();
    void multiModeOff();
    
};

#endif /* OBJObjectMan_hpp */
