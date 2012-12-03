//
//  AmbientLight.cpp
//  raytracer
//
//  Created by Katherine Chen on 12/2/12.
//  Copyright 2012 John Yang-Sammataro. All rights reserved.
//

#include "AmbientLight.h"
#include <stdlib.h>
#include <iostream>
#include <string>

AmbientLight::AmbientLight(float intensity) :
    Light(intensity)
{}

STVector3 AmbientLight::pointToLightVector(const STPoint3& pt) const
{
    //Throw an error if we call this method
    try {
        throw 1;
    } catch (int e) {
        std::cout << "Should not have called this ambient light method." << e << std::endl;
    }
    return STVector3(0, 0, 0);
}

STVector3 AmbientLight::pointToLightVector() const
{
    //Throw an error if we call this method
    try {
        throw 1;
    } catch (int e) {
        std::cout << "Should not have called this ambient light method." << e << std::endl;
    }
    return STVector3(0, 0, 0);
}