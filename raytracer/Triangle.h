//
//  Triangle.h
//  raytracer
//
//  Created by Katherine Chen on 12/2/12.
//  Copyright 2012 John Yang-Sammataro. All rights reserved.
//

#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "st.h"
#include "Shape.h"

class Triangle : public Shape
{
    
public:
    Triangle( const STPoint3& v1,
             const STPoint3& v2,
             const STPoint3& v3);
    
    Triangle( float x1, float y1, float z1,
             float x2, float y2, float z2,
             float x3, float y3, float z3);
    
    bool findPointHit(Ray r, Intersection& intersect, STTransform4 transform) const;
    
private:  
    STPoint3 v1;
    STPoint3 v2;
    STPoint3 v3;
};

#endif