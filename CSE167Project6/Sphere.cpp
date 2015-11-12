//
//  Sphere.cpp
//  CSE167 Spring 2015 Starter Code
//
//  Created by Victor Alor on 10/31/15.
//  Copyright © 2015 RexWest. All rights reserved.
//

#include "Sphere.hpp"
Sphere::Sphere(float radius,int slices,int stacks){
    this->radius = radius;
    this->stacks = stacks;
    this->slices = slices;
    this->material = Material(Color(0.105882f, 0.058824f, 0.113725f), Color(.427451f, .470588f, 0.541176f), Color(.33333f, 0.33333f, .521569f), Color::emissionMaterialDefault(), Color(.7, .89, .69), 127.f);

}
void Sphere::render(){
       glutSolidSphere(radius, slices, stacks);
}