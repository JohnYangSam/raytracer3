//
//  Material.cpp
//  raytracer
//
//  Created by Katherine Chen on 12/2/12.
//  Copyright 2012 John Yang-Sammataro. All rights reserved.
//

#include "Material.h"
#include <vector>

using namespace std;

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

float max(float a, float b) {
    if(a>b) return a;
    return b;
}

bool occluderExists(STPoint3 pt, STVector3 pointToLightSource, std::vector<SceneObject*> sceneObjects) {
    Ray rayToLightSource = Ray(pointToLightSource, pt, 0.01, 1);
    for(int o = 0; o < sceneObjects.size(); ++o) {
        SceneObject* sceneObjectPtr = sceneObjects.at(o);
        if(sceneObjectPtr->intersection(rayToLightSource)) {
            return true;
        }
    }
    return false;
}

STColor3f Material::getColor(STPoint3 intersection, 
                             STVector3 normal, 
                             Camera camera, 
                             std::vector<PointLight>* pLights, 
                             std::vector<DirectionalLight>* dLights, 
                             std::vector<AmbientLight>* aLights, 
                             std::vector<SceneObject*> sceneObjects, 
                             int bounceDepth)
{
    STColor3f ambientTerm = STColor3f(0.,0.,0.);
    STColor3f diffuseTerm = STColor3f(0.,0.,0.);
    STColor3f specularTerm = STColor3f(0.,0.,0.);

    for(int l = 0; l < aLights->size(); l++) {
        ambientTerm += aLights->at(l).getColor();
    }
    ambientTerm *= mAmbient;
    
    for(int l = 0; l < dLights->size(); l++) {
        STVector3 L = dLights->at(l).pointToLightVector();
        L.Normalize();
        if(occluderExists(intersection, L, sceneObjects)) continue;

        STVector3 R = 2.0*STVector3::Dot(L,normal)*normal-L;
        R.Normalize();
        STVector3 V = (-1.0f)*camera.getW();

        diffuseTerm += mDiffuse * dLights->at(l).getColor() * max(0., STVector3::Dot(L, normal));

        specularTerm += mSpecular * dLights->at(l).getColor() * pow(max(0., STVector3::Dot(R, V)), mShine);
    }
    
    for(int l = 0; l < pLights->size(); l++) {
        STVector3 L = pLights->at(l).pointToLightVector(intersection);
        if(occluderExists(intersection, L, sceneObjects)) continue;
        L.Normalize();
        
        STVector3 R = 2.0*STVector3::Dot(L,normal)*normal-L;        
        R.Normalize();
        STVector3 V = camera.getEye() - intersection;
        V.Normalize();
        
        diffuseTerm += mDiffuse * pLights->at(l).getColor() * max(0, STVector3::Dot(L, normal));
        
        specularTerm += mSpecular * pLights->at(l).getColor() * pow(max(0, STVector3::Dot(R, V)), mShine);
    }
    
    return ambientTerm + diffuseTerm + specularTerm;
}