//
//  Material.h
//  raytracer
//
//  Created by Katherine Chen on 12/2/12.
//  Copyright 2012 John Yang-Sammataro. All rights reserved.
//

#ifndef MATERIAL_H
#define MATERIAL_H

#include "st.h"
#include "Light.h"
#include "DirectionalLight.h"
#include "AmbientLight.h"
#include "PointLight.h"
#include "Camera.h"

class Material
{
    
public:
    Material( const STColor3f& ambient,
             const STColor3f& diffuse,
             const STColor3f& specular,
             const STColor3f& mirror,
             float shine);
    
    Material( float ra, float ga, float ba,
             float rd, float gd, float bd,
             float rs, float gs, float bs,
            float rr, float gr, float br,
            float shine);

    
    STColor3f getAmbient() const { return mAmbient; }
    STColor3f getDiffuse() const { return mDiffuse; }
    STColor3f getSpecular() const { return mSpecular; }
    STColor3f getMirror() const { return mMirror; }
    
    STColor3f getColor(STPoint3 intersection, STVector3 normal, Camera camera, std::vector<PointLight> pLights, std::vector<DirectionalLight> dLights, std::vector<AmbientLight> aLights);

    
private:  
    STColor3f mAmbient;
    STColor3f mDiffuse;
    STColor3f mSpecular;
    STColor3f mMirror;
    float mShine;
};

#endif