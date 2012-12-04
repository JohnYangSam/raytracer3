//
//  DirectionalLight.h
//  raytracer
//
//  Created by John Yang-Sammataro on 12/2/12.
//  Copyright (c) 2012 John Yang-Sammataro. All rights reserved.
//

#ifndef __raytracer__DirectionalLight__
#define __raytracer__DirectionalLight__

#include <iostream>

#include "st.h"
#include "Light.h"

class DirectionalLight : protected Light
{
    
public:
    //Ctor
    DirectionalLight(STColor3f color, const STVector3& direction);
    
    //Overide virtual
    STVector3 pointToLightVector(const STPoint3& pt) const;
    //Since we don't actually need th point
    STVector3 pointToLightVector() const;
    
    //Destructor
    ~DirectionalLight();
    
private:
    mutable STVector3 mDirection;
    
};

/* defined(__raytracer__DirectionalLight__) */
#endif
