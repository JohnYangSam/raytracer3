//
//  Shape.h
//  raytracer
//
//  Created by Katherine Chen on 12/2/12.
//  Copyright 2012 John Yang-Sammataro. All rights reserved.
//

#ifndef SHAPE_H
#define SHAPE_H

#include "st.h"
#include "ray.h"

typedef struct Intersection {
    float t;
    STPoint3 intersectionPt;
    STVector3 intersectionNormal;
} Intersection;

class Shape
{

    
public:
    virtual bool findPointHit(Ray r, Intersection& intersect) const;
    
private:  

};

#endif