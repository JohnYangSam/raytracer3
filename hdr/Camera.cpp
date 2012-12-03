//
//  Camera.cpp
//  raytracer
//
//  Created by Katherine Chen on 12/2/12.
//  Copyright 2012 John Yang-Sammataro. All rights reserved.
//

#include "Camera.h"

//Defaults Ctor is empty so it can be initialized later
Camera::Camera() {}

Camera::Camera( const STPoint3& eye,
                const STVector3& up,
                const STPoint3& lookAt,
                float fovy,
                float aspect) :

    mEye(eye),
    mUp(up),
    mLookAt(lookAt),
    mFovy(fovy),
    mAspect(aspect)
{
    //This will take care of necessary normalizations
    Initialize();
}

Camera::Camera( float ex, float ey, float ez,
                float ux, float uy, float uz,
                float lx, float ly, float lz,
                float fovy,
                float aspect) :

    mEye(STPoint3(ex, ey, ez)),
    mUp(STVector3(ux, uy, uz)),
    mLookAt(STPoint3(lx, ly, lz)),
    mFovy(fovy),
    mAspect(aspect)
{
    //This will take care of necessary normalizations
    Initialize();
}

//Initialize the camera variables that need to be
//calculated from the variables passed into the
//initialization list
void Camera::Initialize() {
    //Calculate a (the direction 
    STVector3 a = STVector3(mLookAt - mEye);
    STVector3 b = mUp;
    
    //Normalize a to w
    a.Normalize();
    w = a;

    //Calc and normalize u
    u = STVector3::Cross(b, w);
    u.Normalize();
   
    //v is already normalized
    v = STVector3::Cross(w,u);
}

Ray Camera::generateRay(const STPoint3& pt) const
{
    return Ray(pt, mEye);
}

STVector3 Camera::getU() const { return u; }

STVector3 Camera::getV() const { return v; }

STVector3 Camera::getW() const { return w; }

Camera::~Camera() {}