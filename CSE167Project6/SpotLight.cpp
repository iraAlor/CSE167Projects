//
//  SpotLight.cpp
//  CSE167 Spring 2015 Starter Code
//
//  Created by Victor Alor on 10/29/15.
//  Copyright © 2015 RexWest. All rights reserved.
//

#include "SpotLight.hpp"
SpotLight::SpotLight(float x,float y,float z,Color amb,Color diffuse,Color specular){
    this->position = Vector4(x,y,z,1);
    this->ambientColor = amb;
    this->diffuseColor = diffuse;
    this->specularColor = specular;

    centerSpotLight();
    fov = 45;
    exp = 33;
    
    
}
void SpotLight::centerSpotLight(){
  
}
void SpotLight::bind(int id){
    if(id < 0 || id > 7) {
        std::cout << "ERROR: The light bind ID " << id << " is not valid!" << std::endl;
        return;
    }
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
    glLightf(GL_LIGHT0 + bindID, GL_QUADRATIC_ATTENUATION, 0);
    glLightf(GL_LIGHT0 + bindID, GL_LINEAR_ATTENUATION, 0);
    glLightf(GL_LIGHT0 + bindID, GL_CONSTANT_ATTENUATION, 1);
    //Position the light
   // position.print("FUU");
    glLightfv(GL_LIGHT0 + bindID, GL_POSITION, position.ptr());

    glLightf(GL_LIGHT0 + bindID,GL_SPOT_CUTOFF,fov);
  //  direction.print("dir");
     glLightf(GL_LIGHT0 + bindID,GL_SPOT_EXPONENT,exp);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, (direction.toVector3()).ptr() );
   
/*
 
    */
 
}

void SpotLight::rotateLight(Matrix4 rot){
    this->position = rot*position;
    centerSpotLight();
  
}
void SpotLight::scaleLight(float dir){
    Matrix4 scaly;
    scaly.makeScale(dir);
    this->position = scaly*position;
    
    centerSpotLight();
}
void SpotLight::changeExp(float dir){
    if(dir>0){
    exp++;
    }
    else if(dir<0){
        exp--;
    }
    std::cout<<exp<<" EXP \n";
    exp = exp>128 ? 128 :exp;
    exp = exp<0 ? 0 : exp;
}
void SpotLight::changeFOV(float dir){
    if(dir>0){
        fov++;
    }
    else if(dir<0){
        fov--;
    }
    std::cout<<"FOV "<<fov<<std::endl;
    
    fov = fov>180? 90 :fov;
    fov = fov<0 ? 0 : fov;
}
void SpotLight::unbind(int x){
    
}