#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxFaceTracker.h"

class Mask {
public:
    Mask(int w, int h);
    void setup();
    void updateMask();
    void begin();
    void end();
    
private:
    int                     w, h;
    ofFbo                   maskFbo;
    ofImage                 maskImage;
    ofPixels                maskPixels;
    
    ofxCvColorImage         cvImage;
    ofxCvColorImage         cvMask;
    ofxCvGrayscaleImage     cvGrayMask;
    IplImage*               iplImg;
    IplImage*               iplMask;
    IplImage*               iplGrayMask;
    
    CvScalar                maskFill;
};