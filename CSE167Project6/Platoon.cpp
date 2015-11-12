//
//  Platoon.cpp
//  CSE167 Spring 2015 Starter Code
//
//  Created by Victor Alor on 11/2/15.
//  Copyright © 2015 RexWest. All rights reserved.
//

#include "Platoon.hpp"
Platoon::Platoon(int col, int row, Robot * robo,float center){
    for(int i =0;i<col*row;i++){
        addChild(robo);
    }
    this->row = row;
    this->col = col;
    this->center = center;
    this->robo = robo;
    rot.makeRotateY(M_PI/2.0);
    mode = TRANSLEFT;
    firstOne = MAXSTEPS/2.0;
    counter = 0;
    start = false;
    otherCounter = 0;
}
void Platoon::update1(){
    // std::cout<<"GEN UPDATE"<<std::endl;
    if(!Globals::marchMode){
        return;
    }
    if(mode == TRANSLEFT){
        counter+=1;
        //  std::cout<<"first "<<counter<<std::endl;
        if(counter>=(firstOne)){
            rot.makeRotateY(M_PI);
            mode = TRANSDOWN;
            counter = 0;
        }
    }
    else if(mode == TRANSDOWN){
        counter+=1;
        // std::cout<<"second "<<counter<<std::endl;
        if(counter>=(MAXSTEPS)){
            rot.makeRotateY(1.5*M_PI);
            mode = TRANSRIGHT;
            counter = 0;
        }
    }
    else if(mode == TRANSRIGHT){
        counter+=1;
        if(counter>=MAXSTEPS){
            rot.makeRotateY(2*M_PI);
            mode = TRANSUP;
            counter = 0;
        }
    }
    else if(mode == TRANSUP){
        counter+=1;
        if(counter>=MAXSTEPS){
            rot.makeRotateY(M_PI/2.0);
            mode = TRANSLEFT;
            counter = 0;
            firstOne =MAXSTEPS;
        }
    }
    

    
}
void Platoon::setRotation(int part){
    if(part == 0){
         rot.makeRotateY(M_PI/2.0);
    }
    else if(part == 1){
        rot.makeRotateY(M_PI);
    }
    else if(part == 2){
        rot.makeRotateY(M_PI*1.5);
    }
    else{
          rot.makeRotateY(M_PI*2);
    }
    
}
void Platoon::reset(){
    if(dir == 0){
    rot.makeRotateY(M_PI/2.0);
    mode = TRANSLEFT;
    }
    else{
        rot.makeRotateY(-M_PI/2.0);
        mode = TRANSRIGHT;
    }
    firstOne = MAXSTEPS/2.0;
    counter = 0;
    start = false;
}
void Platoon::update2(){
   // std::cout<<"HERE\n";
    if(!Globals::marchMode){
        return;
    }
    if(mode == TRANSLEFT){
        counter+=1;
        //  std::cout<<"first "<<counter<<std::endl;
        if(counter>=MAXSTEPS){
            rot.makeRotateY(-2*M_PI);
            mode = TRANSDOWN;
            counter = 0;
        }
    }
    else if(mode == TRANSDOWN){
        counter+=1;
        // std::cout<<"second "<<counter<<std::endl;
        if(counter>=(MAXSTEPS)){
            rot.makeRotateY(-1.5*M_PI);
            mode = TRANSLEFT;
            counter = 0;
        }
    }
    else if(mode == TRANSRIGHT){
        counter+=1;
        if(counter>=firstOne){
            rot.makeRotateY(-M_PI);
            mode = TRANSDOWN;
            counter = 0;
        }
    }
    else if(mode == TRANSUP){
        counter+=1;
        if(counter>=MAXSTEPS){
            rot.makeRotateY(-M_PI/2.0);
            mode = TRANSRIGHT;
            counter = 0;
            firstOne =MAXSTEPS;
        }
    }

}
void Platoon::update(){
    /*
    if(Globals::otherCounter>-24 || Globals::controlMode){
        return;
    }
     */
    if(dir == 0){
        update1();
    }
    else{
        update2();
    }
}

void Platoon::draw(Matrix4 m){
    float totalLen = robo->size*col;
    Matrix4 cent;
    cent.makeTranslate(center, 0, 0);
    Matrix4 trans;
    float transFact = -(totalLen/2.0);
    float maxTrans = transFact+totalLen;
    float zTrans = 0;
    Matrix4 zComp;
    zComp.makeTranslate(0, 0, 0);
    Matrix4 fac;
   //rot.makeRotateY(M_PI/2.0);
    fac.identity();
    if((Globals::marchMode || Globals::controlMode)){
        fac = rot;
    }
    for(auto it = children.begin();it!=children.end();it++){
        trans.makeTranslate(transFact, 0, 0);
        (*it)->draw(zComp*m*trans*cent*fac);
        transFact+=robo->size+17;
        if(transFact>= maxTrans){
            transFact = -(totalLen/2.0);
            zTrans-=robo->size+20;
            zComp.makeTranslate(0, 0, zTrans);
        }
    }
}