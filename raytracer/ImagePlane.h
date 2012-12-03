//
//  ImagePlane.h
//  raytracer
//
//  Created by Katherine Chen on 12/2/12.
//  Copyright 2012 John Yang-Sammataro. All rights reserved.
//

#ifndef IMAGEPLANE_H
#define IMAGEPLANE_H

#include "st.h"
#include "Camera.h"

typedef STColor4ub Pixel;

class ImagePlane
{
    
public:
    ImagePlane(const Camera& camera,
               int imgWidth,
               int imgHeight);
   
    //Get the bilerped points in the image plane from
    //two pixel coordinates
    STPoint2 getImagePlane2DPoint(int pixelX, int pixelY) const;
  
    //Pixel operations
    Pixel getBitmapPixel(int pixelX, int pixelY) const;
    void setBitmapPixel(int x, int y, const Pixel& value);
    
    //Saves the STImage of the image plane to a file
    STStatus saveToFile(const std::string& filename);

private:
    //STImage bitmap dimensions
    STImage* mImage;
    const int mBitmapImageHeight;
    const int mBitmapImageWidth;
    
    //Image plane dimensions
    float mImagePlaneHeight;
    float mImagePlaneWidth;
    
    //Image plane bounding points
    STPoint3 UL, UR, LL, LR;
    
};

#endif