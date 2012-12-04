//
//  Light.h
//  raytracer
//
//  Created by Katherine Chen on 12/2/12.
//  Copyright 2012 John Yang-Sammataro. All rights reserved.
//


#ifndef LIGHT_H
#define LIGHT_H

#include "st.h"

class Light
{
    
public:
    //Ctor Implicitly defined
    Light(const STColor3f color);
    
    //Get the vector pointing from a given point to the light
    virtual STVector3 pointToLightVector(const STPoint3& pt) const = 0;
    
    //Get the intensity of the Light
    STColor3f getColor() const;

protected:
    STColor3f mColor;
    
private:  
   };

#endif