//
//  PointLight.cpp
//  CSE167 Spring 2015 Starter Code
//
//  Created by Victor Alor on 10/29/15.
//  Copyright © 2015 RexWest. All rights reserved.
//

#include "PointLight.hpp"
PointLight::PointLight(float x,float y,float z,Color amb,Color diffuse,Color specular){
    this->position = Vector4(x,y,z,1);
    this->ambientColor = amb;
    this->diffuseColor = diffuse;
    this->specularColor = specular;
    
}
void PointLight::bind(int id){
    if(id < 0 || id > 7) {
        std::cout << "ERROR: The light bind ID " << id << " is not valid!" << std::endl;
        return;
    }
    //Set the bindID
    bindID = id;
    
    //Configure the light at the bindID
    glEnable(GL_LIGHT0 + bindID);
    
    //Configure the color of the light
    glLightfv(GL_LIGHT0 + bindID, GL_AMBIENT, ambientColor.ptr());
    glLightfv(GL_LIGHT0 + bindID, GL_DIFFUSE, diffuseColor.ptr());
    glLightfv(GL_LIGHT0 + bindID, GL_SPECULAR, specularColor.ptr());
    
    //Configure the attenuation properties of the light
    //Add support for Constant Attenuation
    //Add support for Linear Attenuation
    glLightf(GL_LIGHT0 + bindID, GL_QUADRATIC_ATTENUATION, .025);
    glLightf(GL_LIGHT0 + bindID, GL_LINEAR_ATTENUATION, 0);
    glLightf(GL_LIGHT0 + bindID, GL_CONSTANT_ATTENUATION, 0);
    //Position the light
    glLightfv(GL_LIGHT0 + bindID, GL_POSITION, position.ptr());
    
   
    
}
void PointLight::rotateLight(Matrix4 rot){
    this->position = rot*position;
    
}
void PointLight::scaleLight(float dir){
    Matrix4 scaly;
    scaly.makeScale(dir);
    this->position = scaly*position;
    
}
void PointLight::unbind(int x){
    
}