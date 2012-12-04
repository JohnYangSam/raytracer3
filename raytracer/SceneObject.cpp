//
//  SceneObject.cpp
//  raytracer
//
//  Created by Katherine Chen on 12/3/12.
//  Copyright 2012 Stanford University. All rights reserved.
//

#include "SceneObject.h"
#include "shape.h"

SceneObject::SceneObject(       Shape*           shape,
                          const Material         material,
                          const STTransform4     transform) :
    mShape(     shape),
    mMaterial(  material),
    mTransform( transform),
    t(-1),
    mInterPt(STPoint3(0,0,0)),
    mInterNormal(STVector3(0,0,0))
{
    
}

bool SceneObject::intersection(Ray ray)
{
    Intersection inter = Intersection();
    bool result     = mShape->findPointHit(ray, inter);
    if(result) {
        t               = inter.t;
        mInterPt        = inter.intersectionPt;
        mInterNormal    = inter.intersectionNormal;
    }
    
    return result;
}

Intersection SceneObject::getIntersection()
{
    if (t == -1) {
        std::cout << "There is a problem" << std::endl;
    }
    Intersection inter;
    inter.t = t;
    inter.intersectionPt = mInterPt;
    inter.intersectionNormal = mInterNormal;
    return inter;
}