//
//  SceneObject.h
//  raytracer
//
//  Created by Katherine Chen on 12/3/12.
//  Copyright 2012 Stanford University. All rights reserved.
//
#ifndef SCENEOBJECT_H

#include "st.h"
#include "Shape.h"
#include "Material.h"

class SceneObject
{
public:
    SceneObject( const Shape* const     shape,
                 const Material&        material,
                 const STTransform4&    transform);

private:
    
    const Shape*        mShape;      // A pointer that can be reassigned
    const Material      mMaterial;   // but the thing it is pointing to
    const STTransform4  mTransform;  // cannot be modified
};


#endif