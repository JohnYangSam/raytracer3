//
//  SceneObject.h
//  raytracer
//
//  Created by Katherine Chen on 12/3/12.
//  Copyright 2012 Stanford University. All rights reserved.
//
#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include "st.h"
#include "Shape.h"
#include "Material.h"

class SceneObject
{
public:
    SceneObject(       Shape*          shape,
                 const Material        material,
                 const STTransform4    transform);
    
    //Finds the intersection and stores it in the intersection
    //piece if it is a valid intersection.  
    bool intersection(Ray ray);
    Intersection getIntersection() { return mIntersection; }
    Material getMaterial() { return mMaterial; }
    Shape* getShapePtr() { return mShape; }
    STTransform4 getTransform() { return mTransform; }
    
private:
    
    Shape*        mShape;      // A pointer that can be reassigned
    Material      mMaterial;   // but the thing it is pointing to
    STTransform4  mTransform;  // cannot be modified
    
    Intersection mIntersection;
};


#endif