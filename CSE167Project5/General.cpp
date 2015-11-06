//
//  General.cpp
//  CSE167 Spring 2015 Starter Code
//
//  Created by Victor Alor on 11/3/15.
//  Copyright © 2015 RexWest. All rights reserved.
//

#include "General.hpp"
General::General(){
    mode = TRANSLEFT;
    rotLeft.makeRotateY(M_PI/2.0);
    currMatrix = rotLeft;
    rotLeft.identity();
    counter = 0;
    coord = Vector3(0,0,0);
    firstOne = MAXSTEPS/2;
    pos = 0;
    firstpass = false;
    otherCounter = 0;
}
void General::reset(){
    mode = TRANSLEFT;
    rotLeft.makeRotateY(M_PI/2.0);
    currMatrix = rotLeft;
    rotLeft.identity();
    counter = 0;
    coord = Vector3(0,0,0);
    firstOne = MAXSTEPS/2;
    pos = 0;
    firstpass = false;
    otherCounter = 0;
}
void General::move(int index, float delta){
    coord[index]+=delta;
}
void General::draw(Matrix4 m){
    ///currMatrix.identity();
    Matrix4 pass = m;
    if(Globals::marchMode){
        pass = m*currMatrix;
    }
    else if(Globals::controlMode){
        Matrix4 tmp;
        tmp.makeTranslate(coord);
        pass = m*tmp;
    }
    else{
        rotLeft.identity();
        counter = 0;
        coord = Vector3(0,0,0);
        firstOne = MAXSTEPS/2;
        pos = 0;
    }
    Group::draw(pass);
}

void General::setSteps(std::vector<int> v){
    steps = v;
}


void General::update(){
   // std::cout<<"GEN UPDATE"<<std::endl;
    if(!Globals::marchMode){
        
        counter = 0;
      //  coord = Vector3(0,0,0);
        firstOne = MAXSTEPS/2;
        pos = 0;
        otherCounter =0;
        return;
    }
/*
    if(Globals::otherCounter>-24){
        currMatrix.identity();
        return;
    }
    if(Globals::controlMode){
        return;
    }
 */
    rotLeft.identity();
    if(mode == TRANSLEFT){
        trans.makeTranslate(counter+coord[0], 0, coord[2]);
        currMatrix = trans;
      //  coord.print("10");
        if(counter>=(firstOne)){
           // rotLeft.makeRotateY(M_PI);
            mode = TRANSDOWN;
            coord[0] = coord[0]+counter;
            counter = 0;
            
        }
    }
    else if(mode == TRANSDOWN){
        
        trans.makeTranslate(coord[0], 0, -counter+coord[2]);
        currMatrix = trans*rotLeft;
        if(counter>=(MAXSTEPS)){
           // rotLeft.makeRotateY(1.5*M_PI);
            mode = TRANSRIGHT;
            coord[2] = coord[2] -counter;
            counter = 0;
        }
    }
    else if(mode == TRANSRIGHT){
        trans.makeTranslate(-counter+coord[0], 0, coord[2]);
        currMatrix = trans*rotLeft;
        if(counter>=MAXSTEPS){
            //rotLeft.makeRotateY(2*M_PI);
            mode = TRANSUP;
            coord[0] -=counter;
            counter = 0;
        }
    }
    else if(mode == TRANSUP){
        trans.makeTranslate(coord[0], 0,coord[2]+counter);
        currMatrix = trans*rotLeft;
        if(counter>=MAXSTEPS){
            //rotLeft.makeRotateY(M_PI/2.0);
            mode = TRANSLEFT;
            coord[2]+=(counter);
            counter = 0;
           // coord.print("1");
            firstOne =MAXSTEPS;
        }
    }
    counter+=1;
    Group::update();


}