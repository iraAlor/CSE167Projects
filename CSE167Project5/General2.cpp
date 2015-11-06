//
//  General2.cpp
//  CSE167 Spring 2015 Starter Code
//
//  Created by Victor Alor on 11/3/15.
//  Copyright © 2015 RexWest. All rights reserved.
//

#include "General2.hpp"
General2::General2(){
    mode = TRANSRIGHT;
    rotLeft.makeRotateY(M_PI/2.0);
    currMatrix = rotLeft;
    rotLeft.identity();
    counter = 0;
    firstOne = MAXSTEPS/2;
    coord  = Vector3(0,0,-26);
   // coord  = Vector3(0,0,0);
    firstpass = true;
    pos = 0;
}
void General2::move(int index, float delta){
    coord[index]+=delta;
}
void General2::reset(){
    mode = TRANSRIGHT;
    rotLeft.makeRotateY(M_PI/2.0);
    currMatrix = rotLeft;
    rotLeft.identity();
    counter = 0;
    firstOne = MAXSTEPS/2;
    coord  = Vector3(0,0,-26);
    firstpass = false;
    pos = 0;
}
void General2::draw(Matrix4 m){
    ///currMatrix.identity();
    //Matrix4 pass = m*currMatrix;
    Matrix4 pass = m;
    if(Globals::marchMode){
        pass = m*currMatrix;
    }
    else if(Globals::controlMode){
        Matrix4 tmp;
        tmp.makeTranslate(coord);
        pass = m*tmp;
    }
    /*
    else{
        mode = TRANSRIGHT;
        rotLeft.identity();
        counter = 0;
        firstOne = MAXSTEPS/2;
        coord  = Vector3(0,0,-24);
        pos = 0;
    }*/
    Group::draw(pass);
}

void General2::update(){
    if(!Globals::marchMode){
         mode = TRANSRIGHT;
        rotLeft.identity();
        counter = 0;
        firstOne = MAXSTEPS/2;
      //  coord  = Vector3(0,0,-20);
        pos = 0;

        return;
    }
    /*
    if(Globals::otherCounter>-24){
        float dlta = -24.0/100.0;
       // std::cout<<"First\n";
        coord[2]+=dlta;
        trans.makeTranslate(0, 0, coord[2]);
        currMatrix = trans*rotLeft;
        return;
    }
    if(coord[2]>-24){
        coord[2] = -26;
    }
    if(Globals::controlMode){
        return;
    }
   */
    rotLeft.identity();
    // std::cout<<"GEN UPDATE"<<std::endl;
    if(mode == TRANSLEFT){
        counter+=1;
        trans.makeTranslate(counter+coord[0], 0, coord[2]);
        currMatrix = trans*rotLeft;
        if(counter>=(MAXSTEPS)){
            // rotLeft.makeRotateY(M_PI);
            coord[0]+=counter;
            mode = TRANSUP;
            counter = 0;
        }
    }
    else if(mode == TRANSDOWN){
        counter+=1;
        trans.makeTranslate(coord[0], 0, -counter+coord[2]);
        currMatrix = trans*rotLeft;
        if(counter>=(MAXSTEPS)){
            // rotLeft.makeRotateY(1.5*M_PI);
            coord[2]-=counter;
            mode = TRANSLEFT;
            counter = 0;
        }
    }
    else if(mode == TRANSRIGHT){
        counter+=1;
        trans.makeTranslate(coord[0]-counter, 0, coord[2]);
        currMatrix = trans*rotLeft;
       // coord.print("20");
        if(counter>=firstOne){
            //rotLeft.makeRotateY(2*M_PI);
            mode = TRANSDOWN;
            coord[0]-=counter;
            counter = 0;
        }
    }
    else if(mode == TRANSUP){
        counter+=1;
        trans.makeTranslate(coord[0], 0, (counter)+coord[2]);
        currMatrix = trans*rotLeft;
        if(counter>=MAXSTEPS){
            //rotLeft.makeRotateY(M_PI/2.0);
            coord[2]+=counter;
            mode = TRANSRIGHT;
            counter = 0;
           
            firstOne =MAXSTEPS;
        }
    }
    
    Group::update();
    
    
}