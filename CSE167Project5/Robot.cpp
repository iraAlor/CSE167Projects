//
//  Robot.cpp
//  CSE167 Spring 2015 Starter Code
//
//  Created by Victor Alor on 10/31/15.
//  Copyright © 2015 RexWest. All rights reserved.
//

#include "Robot.hpp"
Robot::Robot(){
    Robot::Robot(1,1);
}

Robot::Robot(float sRad,float cL){
    Matrix4 tmp;
    MatrixTransform * scaleCube = new MatrixTransform(tmp.makeScale(cL));
    MatrixTransform * scaleSphere = new MatrixTransform(tmp.makeScale(sRad));
    MatrixTransform * rotateLeft = new Appendage(-1);
    MatrixTransform * rotateRight = new Appendage(1);
    Cube * cube = new Cube(1);
    cube->boundingSphere =  BoundingShpere(Vector4(0, 0, 0, 1),.9);
    Sphere * sphere = new Sphere(1,100,100);
    sphere->boundingSphere = BoundingShpere(Vector4(0, 0, 0, 1),1.1);
    
    
    //Creating left Side
    
    //arm
    MatrixTransform * trans = new MatrixTransform(tmp.makeTranslate(-sRad-(cL/2.0), 0, 0));
    addChild(trans);
    MatrixTransform * transRot = new MatrixTransform(tmp.makeTranslate((cL/2.0),(cL/2) , -(cL/2)));
   // scaleCube->addChild(trans);
    trans->addChild(transRot);
    transRot->addChild(rotateLeft);
    transRot = new MatrixTransform(tmp.makeTranslate(-(cL/2), -(cL/2), (cL/2)));
    rotateLeft->addChild(transRot);
    transRot->addChild(scaleCube);
    scaleCube->addChild(cube);
    
    
    //leg
    
    trans = new MatrixTransform(tmp.makeTranslate(-(cL/2), -sRad-(cL/2.0)-.1, 0));
    addChild(trans);
    transRot = new MatrixTransform(tmp.makeTranslate((cL/2.0), (cL/2.0), -(cL/2)));
    trans->addChild(transRot);
    transRot->addChild(rotateLeft);
    transRot = new MatrixTransform(tmp.makeTranslate(-(cL/2.0), -(cL/2.0), (cL/2)));
    rotateLeft->addChild(transRot);
    transRot->addChild(scaleCube);
    scaleCube->addChild(cube);

    
    //Creating Right Side
    //Arm
    
    trans = new MatrixTransform(tmp.makeTranslate(sRad+(cL/2.0), 0, 0));
    addChild(trans);
    transRot  = new MatrixTransform(tmp.makeTranslate(-(cL/2), (cL/2), -(cL/2)));
    trans->addChild(transRot);
    transRot->addChild(rotateRight);
    transRot = new MatrixTransform(tmp.makeTranslate((cL/2.0), -(cL/2.0), (cL/2) ));
    rotateRight->addChild(transRot);
    transRot->addChild(scaleCube);
    scaleCube->addChild(cube);
    
    
    //Leg
    trans= new MatrixTransform(tmp.makeTranslate((cL/2), -sRad-(cL/2)-.1, 0));
    addChild(trans);
    transRot  = new MatrixTransform(tmp.makeTranslate(-(cL/2.0), (cL/2.0), -(cL/2)));
    trans->addChild(transRot);
    transRot->addChild(rotateRight);
    transRot = new MatrixTransform(tmp.makeTranslate((cL/2.0), -(cL/2.0), (cL/2)));
    rotateRight->addChild(transRot);
    transRot->addChild(scaleCube);
    scaleCube->addChild(cube);
    
    //Creating Body
    tmp.identity();
    MatrixTransform *temp = new MatrixTransform(tmp);
    temp->addChild(sphere);
    scaleSphere->addChild(temp);
    addChild(scaleSphere);
    
    
    //Creating Head
 
    temp = new MatrixTransform(tmp.makeTranslate(0,sRad+(cL/2),0));
    addChild(temp);
    temp->addChild(scaleCube);
    scaleCube->addChild(cube);
    
    boundingSphere = BoundingShpere(Vector4(0, 0, 0, 1), sRad+cL+4);
    size = sRad+cL+2;
                               
}




void Robot::draw(Matrix4 m){
    if(Globals::frustum.contains(boundingSphere,m)==Frustum::OUTSIDE && Globals::cullMode){
       // std::cout<<"red\n";
        return;
    }
    if(Globals::bsMode){
       this->boundingSphere.tempMat = m;
     //this->boundingSphere.display(m);
       Globals::g1.push_back(new BoundingShpere(&(this->boundingSphere)));
       
    }
   // std::cout<<"drawn"<<std::endl;
    for(auto it =children.begin();it!=children.end();it++){
        (*it)->draw(m);
    }
    if(Globals::bsMode){
        Globals::g2.push_front(Globals::temp);
    Globals::temp = {};
        //std::cout<<"HERE\n";
    }
}