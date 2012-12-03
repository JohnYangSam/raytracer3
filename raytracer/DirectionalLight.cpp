//
//  DirectionalLight.cpp
//  raytracer
//
//  Created by Katherine Chen on 12/2/12.
//  Copyright 2012 John Yang-Sammataro. All rights reserved.
//

#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(float intensity, const STVector3& direction) :

Light(intensity),
mDirection(STVector3(direction))
{
    mDirection.Normalize();
}

STVector3 DirectionalLight::pointToLightVector(const STPoint3& pt) const
{
    //Return the opposite of the direction vector
    STVector3 result = mDirection * (-1.0f);
    //Normalize
    result.Normalize();
    return result;
}

STVector3 DirectionalLight::pointToLightVector() const
{
    STVector3 result = mDirection * (-1.0f);
    //Normalize
    result.Normalize();
    return result;
}

DirectionalLight::~DirectionalLight()
{}

