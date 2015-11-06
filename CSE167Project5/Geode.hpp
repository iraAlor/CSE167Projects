//
//  Geode.hpp
//  CSE167 Spring 2015 Starter Code
//
//  Created by Victor Alor on 10/31/15.
//  Copyright © 2015 RexWest. All rights reserved.
//

#ifndef Geode_hpp
#define Geode_hpp

#include <stdio.h>
#include <GLUT/glut.h>

#include "Node.hpp"
class Geode : public Node{
public:
    Material material;
    virtual void render()=0;
    void draw(Matrix4 m){
        material.apply();
        glMatrixMode(GL_MODELVIEW);
        
        //Push a save state onto the matrix stack, and multiply in the toWorld matrix
        glPushMatrix();
        glMultMatrixf(m.ptr());
        render();
        glPopMatrix();
        if(Globals::bsMode){
          //  boundi
            boundingSphere.display(m);
            //boundingSphere.set(m);
            //Globals::temp.push_front(new BoundingShpere(&boundingSphere));
           // std::cout<<Globals::temp.front()->radius<<std::endl;
            
        }
    }
    void update(){}
    
};

#endif /* Geode_hpp */
