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
    SceneObject( const Shape* const shape,
                const Material& material,
                const STTransform4& transform);

private:
    Shape* mShape;
    Material mMaterial;
    STTransform4 mTransform;
};


#endif