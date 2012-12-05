//
//  Sphere.h
//  raytracer
//
//  Created by Katherine Chen on 12/2/12.
//  Copyright 2012 John Yang-Sammataro. All rights reserved.
//

#ifndef SPHERE_H
#define SPHERE_H

#include "st.h"
#include "Shape.h"

class Sphere : public Shape
{
    
public:
    Sphere( const STPoint3& center,
           float r);
    
    Sphere( float cx, float cy, float cz,
           float r);
    
    bool findPointHit(Ray r, Intersection& intersect, STTransform4 transform) const;
    
private:  
    STPoint3 mCenter;
    float mRadius;
};

#endif