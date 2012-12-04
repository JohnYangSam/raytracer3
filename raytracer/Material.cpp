//
//  Material.cpp
//  raytracer
//
//  Created by Katherine Chen on 12/2/12.
//  Copyright 2012 John Yang-Sammataro. All rights reserved.
//

#include "Material.h"

Material::Material( const STColor3f& ambient,
                   const STColor3f& diffuse,
                   const STColor3f& specular,
                   const STColor3f& mirror,
                   float shine) :
mAmbient(ambient),
mDiffuse(diffuse),
mSpecular(specular),
mMirror(mirror),
mShine(shine)
{
    
}

Material::Material( float ra, float ga, float ba,
                   float rd, float gd, float bd,
                   float rs, float gs, float bs,
                   float rr, float gr, float br,
                   float shine) :
mAmbient(STColor3f(ra, ga, ba)),
mDiffuse(STColor3f(rd, gd, bd)),
mSpecular(STColor3f(rs, gs, bs)),
mMirror(STColor3f(rr, gr, br)),
mShine(shine)
{
    
}

STColor3f Material::getColor(STPoint3 intersection, STVector3 normal, Camera camera, std::vector<PointLight> pLights, std::vector<DirectionalLight> dLights, std::vector<AmbientLight> aLights) 
{
    STColor3f ambientIntensity = STColor3f(0.,0.,0.);
    for(int l = 0; l < aLights.size(); l++) {
        ambientIntensity += aLights[l].getIntensity();
    }
    STColor3f ambientTerm = mAmbient * ambientIntensity;
    
    
}