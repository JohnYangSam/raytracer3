//
//  ImagePlane.cpp
//  raytracer
//
//  Created by Katherine Chen on 12/2/12.
//  Copyright 2012 John Yang-Sammataro. All rights reserved.
//

#include "ImagePlane.h"

#include <iostream>
#include <iomanip>

using namespace std;

#define HALF_PIXEL 0.5f

ImagePlane::ImagePlane(const Camera& camera,
                       int imgWidth,
                       int imgHeight) :

    mBitmapImageWidth(imgWidth),
    mBitmapImageHeight(imgHeight)
{
    mImage = new STImage(mBitmapImageWidth,
                         mBitmapImageHeight,
                         STColor4ub(0, 0, 0, 255)
            );

    //See slides for diagram
    //C = center point of the image plane
    //x and y are the offsets from the center to the edges
    // i.e. (the angles in radians then multiplied times w's length (which is 1)
    STPoint3 C = camera.getEye() + camera.getW();
    float y = tan(camera.getFovy() / 2);
    float x = tan(camera.getAspect() * camera.getFovy() / 2);
        
    LL = C + (x * camera.getU()) - (y * camera.getV());
    UL = C + (x * camera.getU()) + (y * camera.getV());
    LR = C - (x * camera.getU()) - (y * camera.getV());
    UR = C - (x * camera.getU()) + (y * camera.getV());
    
    mImagePlaneWidth = 2 * x;
    mImagePlaneHeight = 2 * y;
    
}

// Get the image plane plane point using bilinear interpolation
// on the bitmap coordinates with respect to the bitmap and image plane
// dimensions.
//
// Note: The .05 float or pound define enters the pixel inside the edges of
// the image plane since the usual pixel integers refer to the bottom
// left corner of the pixel but we want the center of the pixel
// (hence adding .5)
//
//
//
STPoint3 ImagePlane::getImagePlanePoint(int pixelX, int pixelY) const
{
    //u and v are between [0, 1] representing how far along the
    //image plane we are
    float u = (pixelX + HALF_PIXEL) / mBitmapImageWidth;
    float v = (pixelY + HALF_PIXEL) / mBitmapImageHeight;
   
    //WEIGHTED AVERAGES
    STVector3 result = ( STVector3(LL) * (1 - v) + STVector3(UL)*(v) ) * (1 - u)
    + (STVector3(LR) * (1 - v) + STVector3(UR) * (v)) * (u);
    
    return STPoint3(result);
}

Pixel ImagePlane::getBitmapPixel(int x, int y) const
{
    return mImage->GetPixel(x, y);    
}

void ImagePlane::setBitmapPixel(int x, int y, const Pixel& value)
{
    mImage->SetPixel(x, y, value);
}

STStatus ImagePlane::saveToFile(const std::string& filename)
{
    return mImage->Save(filename);
}

int ImagePlane::getBitmapHeight()  const { return mBitmapImageHeight; }
int ImagePlane::getBitmapWidth()   const { return mBitmapImageWidth;  }

float ImagePlane::getPlaneHeight() const { return mImagePlaneHeight; }
float ImagePlane::getPlaneWidth()  const { return mImagePlaneWidth;  }
