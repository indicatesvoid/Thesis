#include "Mask.h"

Mask::Mask(int w, int h) {
    this->w = w;
    this->h = h;
    
    // color of masked part
    this->maskFill = cvScalarAll(36);
}

void Mask::setup() {
    // allocate FBOs for mask and pixelface
    maskFbo.allocate(w, h, GL_RGB);
    maskPixels.allocate(w, h, OF_PIXELS_RGB);
    maskImage.allocate(w, h, OF_IMAGE_COLOR);
    
    // allocate openCv shit
    cvImage.allocate(w, h);
    cvMask.allocate(w, h);
    cvGrayMask.allocate(w, h);
    iplImg = cvImage.getCvImage();
    iplGrayMask = cvGrayMask.getCvImage();
    iplMask = cvMask.getCvImage();
}

void Mask::updateMask() {
    cvMask.setFromPixels(maskImage.getPixels(), w, h);
    cvInRangeS(iplMask, cvScalarAll(250), cvScalarAll(255), iplGrayMask);
}

void Mask::begin() {
    maskFbo.begin();
}

void Mask::end() {
    maskFbo.end();
}
