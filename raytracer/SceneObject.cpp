//
//  SceneObject.cpp
//  raytracer
//
//  Created by Katherine Chen on 12/3/12.
//  Copyright 2012 Stanford University. All rights reserved.
//

#include "SceneObject.h"

SceneObject::SceneObject(       Shape*           shape,
                          const Material         material,
                          const STTransform4     transform) :
    mShape(     shape),
    mMaterial(  material),
    mTransform( transform) 
{
    
}