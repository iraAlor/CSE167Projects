//
//  Group.cpp
//  CSE167 Spring 2015 Starter Code
//
//  Created by Victor Alor on 10/31/15.
//  Copyright © 2015 RexWest. All rights reserved.
//

#include "Group.hpp"

void Group::update(){
    //std::cout<<"UPDATE\n";
    for(auto it =children.begin();it!=children.end();it++){
        (*it)->update();
    }
}

void Group::draw(Matrix4 m){
    for(auto it =children.begin();it!=children.end();it++){
        (*it)->draw(m);
    }
}
void Group::addChild(Node * a){
    children.push_back(a);
    
}
void Group::addChild(Node *(*spawn)()){
    children.push_back((*spawn)());
}
void Group::removeChild(Node * sub){
    children.remove(sub);
}
void Group::removeChild(){
    if(!children.empty()){
      children.pop_back();
    }
}
