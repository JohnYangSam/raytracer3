//
//  PointLight.cpp
//  raytracer
//
//  Created by Katherine Chen on 12/2/12.
//  Copyright 2012 John Yang-Sammataro. All rights reserved.
//

#include "PointLight.h"

PointLight::PointLight(float intensity, const STPoint3& positionPt) :
    Light(intensity),
    mPosition(STPoint3(positionPt))
{}

STVector3 PointLight::pointToLightVector(const STPoint3& pt) const
{
    //Calculate new vec
    STVector3 result = STVector3(mPosition - pt);
    //Normalize
    result.Normalize();
    return result;
}

PointLight::~PointLight()
{}