//
//  Triangle.cpp
//  raytracer
//
//  Created by Katherine Chen on 12/2/12.
//  Copyright 2012 John Yang-Sammataro. All rights reserved.
//

#include "Triangle.h"

Triangle::Triangle( const STPoint3& v1,
         const STPoint3& v2,
         const STPoint3& v3) : 
    v1(v1),
    v2(v2),
    v3(v3) 
{}

Triangle::Triangle( float x1, float y1, float z1,
         float x2, float y2, float z2,
                   float x3, float y3, float z3) :
v1(STPoint3(x1,y1,z1)),
v2(STPoint3(x2,y2,z2)),
v3(STPoint3(x3,y3,z3))
{}

bool Triangle::findPointHit(Ray r, Intersection& intersect, STTransform4 transform) const{
   
    //Transform points according to the scene object transformation
    STPoint3 v11 = transform * v1;
    STPoint3 v21 = transform * v2;
    STPoint3 v31 = transform * v3;
    
    // Using Cramer's rule
    float a = v11.x - v21.x;
    float b = v11.y - v21.y;
    float c = v11.z - v21.z;
    float d = v11.x - v31.x;
    float e = v11.y - v31.y;
    float f = v11.z - v31.z;
    float g = r.getD().x;
    float h = r.getD().y;
    float i = r.getD().z;
    float j = v11.x - r.getE().x;
    float k = v11.y - r.getE().y;
    float l = v11.z - r.getE().z;
    
    float ei_minus_hf = e * i - h * f;
    float gf_minus_di = g * f - d * i;
    float dh_minus_eg = d * h - e * g;
    float ak_minus_jb = a * k - j * b;
    float jc_minus_al = j * c - a * l;
    float bl_minus_kc = b * l - k * c;
    
    float M = a*ei_minus_hf + b*gf_minus_di + c*dh_minus_eg;
    float t = -(f*ak_minus_jb + e*jc_minus_al + d*bl_minus_kc) / M;
    if(t < r.getMinT() || t > r.getMaxT()) return false;
    float gamma = (i*ak_minus_jb + h*jc_minus_al + g*bl_minus_kc) / M;
    if(gamma < 0 || gamma > 1) return false;
    float beta = (j*ei_minus_hf + k*gf_minus_di + l*dh_minus_eg) / M;
    if(beta < 0 || beta > 1 - gamma) return false;
    
    intersect.t = t;
    intersect.intersectionPt = r.getE() + t * r.getD();
    
    //We are getting the (untransformed normal here!)
    STVector3 normal = STVector3::Cross(v2-v1,v3-v2);
    
    //Transform normal into world coordinates according to "transoform"
    // new normal = M^(-T)(normal, 0) (where normal,0 is the normal in 4D
    normal = transform.Inverse().Transpose() * normal;
    normal.Normalize();
    
    intersect.intersectionNormal = normal;
    return true;

}
