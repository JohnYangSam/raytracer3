//
//  ImagePlane.cpp
//  raytracer
//
//  Created by Katherine Chen on 12/2/12.
//  Copyright 2012 John Yang-Sammataro. All rights reserved.
//

#include "ImagePlane.h"
#define HALF_PIXEL 0.05f

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
STPoint2 ImagePlane::getImagePlane2DPoint(int pixelX, int pixelY) const
{
    // These are the x and y are the coordinates in the Image plane if we had
    // orthographic perspective
    float u = LL.x + ( (LR.x - LL.x) / mBitmapImageWidth ) * (pixelX + HALF_PIXEL);
    float v = LL.y + ( (UL.y - LL.y) / mBitmapImageHeight ) * (pixelY + HALF_PIXEL);
   
    return STPoint2(u,v);
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