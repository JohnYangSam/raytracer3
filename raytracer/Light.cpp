//
//  Light.cpp
//  raytracer
//
//  Created by Katherine Chen on 12/2/12.
//  Copyright 2012 John Yang-Sammataro. All rights reserved.
//

#include "Light.h"

//Constructor initializes intensity with an initialization list element
Light::Light(STColor3f color) :
mColor(color)
{}

STColor3f Light::getColor() const
{
    return mColor;
}