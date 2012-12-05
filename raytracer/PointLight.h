//
//  PointLight.h
//  raytracer
//
//  Created by Katherine Chen on 12/2/12.
//  Copyright 2012 John Yang-Sammataro. All rights reserved.
//

#ifndef POINTLIGHT_H
#define POINTLIGHT_H
#include "st.h"
#include "Light.h"

class PointLight : public Light
{
    
public:
    //Ctor
    PointLight(STColor3f color, const STPoint3& positionPt, const STTransform4& transform);
    
    //Overide virtual
    STVector3 pointToLightVector(const STPoint3& pt) const;
    
    STPoint3 getPosition() { return mPosition; } const;
    
    //Destructor
    ~PointLight();
    
private:
    STPoint3 mPosition;
    
};

#endif