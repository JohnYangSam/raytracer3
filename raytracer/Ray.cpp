//
//  Ray.cpp
//  raytracer
//
//  Created by Katherine Chen on 12/2/12.
//  Copyright 2012 John Yang-Sammataro. All rights reserved.
//

#include "Ray.h"

Ray::Ray(const STPoint3& point,
         const STPoint3& cameraEyePos,
         float minT,
         float maxT) :

    mMinT(minT),
    mMaxT(maxT),
    e(cameraEyePos)
    /* d initialized below */
{
    //Create and normalize the d vector
    direction = STVector3(point - e);
    direction.Normalize();
}

Ray::Ray(const STVector3& direction,
         const STPoint3& cameraEyePos,
         float minT,
         float maxT) :

    mMinT(minT),
    mMaxT(maxT),
    e(cameraEyePos)
{
    //Create and normalize the d vector
    this->direction = direction;
    this->direction.Normalize();
}