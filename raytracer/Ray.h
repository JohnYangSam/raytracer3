//
//  Ray.h
//  raytracer
//
//  Created by Katherine Chen on 12/2/12.
//  Copyright 2012 John Yang-Sammataro. All rights reserved.
//

#ifndef RAY_H
#define RAY_H

#include "st.h"

class Ray
{
    
public:
    Ray(const STPoint3& point,
        const STPoint3& cameraEyePos,
        float minT = 0,
        float maxT = 0);
    
    Ray(const STVector3& direction,
        const STPoint3& cameraEyePos,
        float minT = 0,
        float maxT = 0);

    STPoint3 getE() const{ return e; }
    STVector3 getD() const{ return d; }
    float getMinT() const{ return mMinT; }
    float getMaxT() const{ return mMaxT; }

private:  
    float mMinT;
    float mMaxT;
    STPoint3 e;
    STVector3 d;
};

#endif