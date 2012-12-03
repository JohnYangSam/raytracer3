//
//  Sphere.cpp
//  raytracer
//
//  Created by Katherine Chen on 12/2/12.
//  Copyright 2012 John Yang-Sammataro. All rights reserved.
//

#include "Sphere.h"

Sphere::Sphere( const STPoint3& center,
               float r) :
    mCenter(center),
    mRadius(r)
{
    
}

Sphere::Sphere( float cx, float cy, float cz,
               float r) :
    mCenter(STPoint3(cx, cy, cz)),
    mRadius(r)
{
    
}

float min(float a, float b) {
    if (a < b) return a;
    return b;
}

bool Sphere::findPointHit(Ray r, Intersection& intersect) const{
    STVector3 e_minus_c = r.getE() - mCenter;
    STVector3 d = r.getD();
    
    float a = STVector3::Dot(d, d);
    float b = 2 * STVector3::Dot(d, e_minus_c);
    float c = STVector3::Dot(e_minus_c, e_minus_c) - mRadius * mRadius;
    
    float t;
    
    float discriminant = b * b - 4 * a * c;
    if(discriminant < 0) { // no solutions
       return false; 
    } else if (discriminant == 0) { // 1 solution
        t = (-b + sqrt(discriminant)) / (2 * a);
    } else { // 2 solutions, pick smaller t which is closer to eye
        t = min((-b + sqrt(discriminant)) / (2 * a), (-b - sqrt(discriminant)) / (2 * a));
    }
    intersect.t = t;
    intersect.intersectionPt = r.getE() + t * d;
    intersect.intersectionNormal = (intersect.intersectionPt - mCenter) / mRadius;
    return true;
}