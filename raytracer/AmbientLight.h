//
//  AmbientLight.h
//  raytracer
//
//  Created by Katherine Chen on 12/2/12.
//  Copyright 2012 John Yang-Sammataro. All rights reserved.
//

#ifndef AMBIENTLIGHT_H
#define AMBIENTLIGHT_H

#include "st.h"
#include "Light.h"

class AmbientLight : public Light
{
    
public:
    //Ctor
    AmbientLight(STColor3f color);
    
    //Overide virtual
    STVector3 pointToLightVector(const STPoint3& pt) const;
    //Since we technically don't need to take in the point
    STVector3 pointToLightVector() const;
    
private:  

};

#endif