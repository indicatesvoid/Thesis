#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxFaceTracker.h"
#include "ofxPostProcessing.h"

class ExpressionAnalyzer : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
    
        void applyMask();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
private:
    ofVideoGrabber          cam;
    ofxFaceTracker          tracker;
    ExpressionClassifier    classifier;
    int                     cIndex;
    
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
    
    ofxPostProcessing post;
		
};
