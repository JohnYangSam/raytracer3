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
    SceneObject( Shape*          shape,
                 Material        material,
                 STTransform4    transform);

private:
    
    Shape*        mShape;      // A pointer that can be reassigned
    Material      mMaterial;   // but the thing it is pointing to
    STTransform4  mTransform;  // cannot be modified
};


#endif