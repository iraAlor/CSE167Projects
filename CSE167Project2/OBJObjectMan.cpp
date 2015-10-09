//
//  OBJObjectMan.cpp
//  CSE167 Spring 2015 Starter Code
//
//  Created by Victor Alor on 10/6/15.
//  Copyright © 2015 RexWest. All rights reserved.
//

#include "OBJObjectMan.hpp"

OBJObjectMan::OBJObjectMan(){
    
}
OBJObjectMan::~OBJObjectMan(){

    for(auto it = dmap.begin();it!=dmap.end();it++){
        for (auto k = (*it).second->begin();k<(*it).second->end();k++){
            delete *k;
        }
        delete (*it).second;
    }
    
}
OBJObject * OBJObjectMan::getObject(std::string fname){
    
    if(mapy.end()!= mapy.find(fname)){
        return new OBJObject(mapy[fname]);
    }
  
    OBJObject * a = new OBJObject(fname);
   // OBJObject b = OBJObject(fname);
    mapy[fname] = a;

    OBJObject * s = new OBJObject(a);
    s->toWorld.identity();
    return s;
}
void OBJObjectMan::drawStuff(DrawData& d){
    std::vector<Drawable*> * cvect =  dmap[mode];
    for(auto it = cvect->begin();it!=cvect->end();it++){
        (*it)->draw(d);
    }
}
void OBJObjectMan::updateStuff(UpdateData& u){
    std::vector<Drawable*> * cvect =  dmap[mode];
    for(auto it = cvect->begin();it!=cvect->end();it++){
        (*it)->update(u);
    }
    
}
void OBJObjectMan::addDrawMode(int i ){
    if (dmap.end() == dmap.find(i)){
       dmap[i] = new std::vector<Drawable*>();
    }
    else{
        dmap[i]->clear();
    }
}
void OBJObjectMan::setMode(int i){
    mode = i;
    
}
void OBJObjectMan::setMode(int i,std::string fname){
    setMode(i);
   
    if( dmap.find(i) == dmap.end() || dmap[i]->size()<1){
        addDrawMode(i);
       
        OBJObject * c = getObject(fname);
        c->toWorld.identity();
        dmap[i]->push_back(c);
    }
    
}
void OBJObjectMan::addToMode(int i,Drawable * sub){
    if(dmap.find(i) == dmap.end()){
        addDrawMode(i);
       
    }
    dmap[i]->push_back(sub);
    
}
void OBJObjectMan::changeOne(void (Drawable::*fptr)(float),float a){
    std::vector<Drawable*> * cvect =  dmap[mode];
    if(cvect->size()<=0){
        return;
    }
   // for(auto it = cvect->begin();it!=cvect->end();it++){
        ((*(cvect->back())).*fptr)(a);//call: Foo::f() through an object
    //}
}
void OBJObjectMan::changeZero(void (Drawable::*fptr)()){
    std::vector<Drawable*> * cvect =  dmap[mode];
    if(cvect->size()<=0){
        return;
    }
    //for(auto it = cvect->begin();it!=cvect->end();it++){
     //   ((**it).*fptr)();//call: Foo::f() through an object
   // }
     ((*(cvect->back())).*fptr)();
}
void OBJObjectMan::changeThree(void (Drawable::*fptr)(float,float,float),float a,float b,float c){
    std::vector<Drawable*> * cvect =  dmap[mode];
    if(cvect->size()<=0){
        return;
    }
    /*
    for(auto it = cvect->begin();it!=cvect->end();it++){
        ((**it).*fptr)(a,b,c);//call: Foo::f() through an object
    }*/
    ((*(cvect->back())).*fptr)(a,b,c);
}
void OBJObjectMan::reset(){
    std::vector<Drawable*> * vec = dmap[mode];
    unsigned long size =vec->size();
    if(size<=0){
        return;
    }
    Drawable * head = vec->at(0);
    for(int j = 1;j<size;j++){
        delete vec->at(j);
    }
    vec->clear();
    head->reset();
    vec->push_back(head);
}
void OBJObjectMan::multiMode(){
    dmap[8] = new std::vector<Drawable*>();
    if(dmap[mode]->size()>0 && mode >1){
      dmap[8]->push_back(new OBJObject((OBJObject*)dmap[mode]->back()));
       ((OBJObject*) dmap[8]->at(0))->spinDir =((OBJObject*)dmap[mode]->back())->spinDir;
        ((OBJObject*) dmap[8]->at(0))->toWorld =((OBJObject*)dmap[mode]->back())->toWorld;
    }
    mode = 8;
}
void OBJObjectMan::multiModeOff()
{
    mode = oldMode;
    if(dmap[8]){
        delete dmap[8];
    }
    
}
void OBJObjectMan::addToMode(int i,std::string fname){
    if(dmap.find(i) == dmap.end()){
        addDrawMode(i);
    }
    dmap[i]->push_back(getObject(fname));
}