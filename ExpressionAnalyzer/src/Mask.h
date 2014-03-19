#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxFaceTracker.h"

class Mask {
public:
    Mask(int w, int h, bool alphaMask = true);
    void setup();
    void updateMask(const unsigned char *pixels);
//    void updateMask(const unsigned char *maskPixels, ofImage top);
    void begin();
    void end();
    
    void draw(int x, int y);
    void drawMask(int x, int y);
    
private:
    void allocate();
    
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
    
    ofShader                maskShader;
    ofImage                 topLayer;
    ofImage                 bottomLayer;
    ofImage                 alphaMaskImage;
    bool                    alphaMask;
};