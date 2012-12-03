//
//  Camera.h
//  raytracer
//
//  Created by Katherine Chen on 12/2/12.
//  Copyright 2012 John Yang-Sammataro. All rights reserved.
//

#ifndef CAMERA_H
#define CAMERA_H

#include "st.h"
#include "Ray.h"

class Camera
{

public:
    
    //Ctors
    
    //Default Ctor
    Camera();
    
    Camera( const STPoint3& eye,
            const STVector3& up,
            const STPoint3& lookAt,
            float fovy,
            float aspect);
    
    Camera( float ex, float ey, float ez,
            float ux, float uy, float uz,
            float lx, float ly, float lz,
            float fovy,
            float aspect);
    
    //Generates and returns a ray class instance from the
    //camera to the inputted point
    Ray generateRay(const STPoint3& pt) const;
    
    float getFovy() const{ return mFovy; }
    
    float getAspect() const { return mAspect; }
    
    STPoint3 getEye() const { return mEye; }
    
    STVector3 getU() const;
    STVector3 getV() const;
    STVector3 getW() const;
    
    //Destructor
    ~Camera();
    
private:
    
    STPoint3 mEye;
    
    //These two are used for calculations but ultimately
    // v and w respectively
    STVector3 mUp;
    STPoint3 mLookAt;

    float mFovy;
    float mAspect;
    STVector3 u; // u = normalized  leftward  vector (i.e. the cross of the two below)
    STVector3 v; // v = normalized  up        vector (i.e. up)
    STVector3 w; // w = normalized  direction vector (i.e. look at point - eye point)
    
    void Initialize();
};

#endif