//
//  Light.cpp
//  raytracer
//
//  Created by Katherine Chen on 12/2/12.
//  Copyright 2012 John Yang-Sammataro. All rights reserved.
//

#include "Light.h"

//Constructor initializes intensity with an initialization list element
Light::Light(float intensity) :
mIntensity(intensity)
{}

float Light::getIntensity() const
{
    return mIntensity;
}