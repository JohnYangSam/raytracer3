//
//  Sphere.cpp
//  raytracer
//
//  Created by Katherine Chen on 12/2/12.
//  Copyright 2012 John Yang-Sammataro. All rights reserved.
//

#include "Sphere.h"
#include <assert.h>

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

bool Sphere::findPointHit(Ray r, Intersection& intersect, STTransform4 transform) const{

    //Convert ray with M^(-1)
    Ray transformedRay = Ray(transform.Inverse() * r.getD(),
                            transform.Inverse() * r.getE());
    
    STVector3 e_minus_c = (transformedRay.getE() - mCenter);
    STVector3 d = (transformedRay.getD());
    
    float a = STVector3::Dot(d, d);
    float b = 2 * STVector3::Dot(d, e_minus_c);
    float c = STVector3::Dot(e_minus_c, e_minus_c) - mRadius * mRadius;
    
    float t;
    
    float discriminant = b * b - 4 * a * c;
    if(discriminant < 0) { // no solutions
       return false; 
    } else if (discriminant == 0) { // 1 solution
        t = (-b + sqrt(discriminant)) / (2 * a);
    } else { // 2 solutions, pick smaller t > 0 which is closer to eye
        float result1 = (-b + sqrt(discriminant)) / (2 * a);
        float result2 = (-b - sqrt(discriminant)) / (2 * a);
        
        //Pick the smallest which is greater than 0
        if (result1 < 0) {
            t = result2;
        } else if (result2 < 0) {
            t = result1;
        } else {
            t = min(result1, result2);
        }
        
    }
    intersect.t = t;
    STPoint3 untransformedHit = (transformedRay.getE() + t * d);
    intersect.intersectionPt = transform * untransformedHit;
    
    // Untransformed normal
    STVector3 normal = (untransformedHit - mCenter);
    // Tranformed normal
    normal = transform.Inverse().Transpose() * normal;
    normal.Normalize();
    intersect.intersectionNormal = normal;
   
    //INCLUDE THE BIAS so that this doesn't revert on itself!
    if(t < r.getMinT() || t > r.getMaxT()) return false;
    
    return true;
}