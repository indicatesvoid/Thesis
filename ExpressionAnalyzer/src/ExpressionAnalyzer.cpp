#include "ExpressionAnalyzer.h"

using namespace ofxCv;
using namespace cv;

#define CAM_WIDTH 640
#define CAM_HEIGHT 480

//--------------------------------------------------------------
void ExpressionAnalyzer::setup(){
    cam.initGrabber(640,480);
    tracker.setup();
    tracker.setRescale(0.5);
    
    // allocate FBOs for mask and pixelface
    maskFbo.allocate(CAM_WIDTH, CAM_HEIGHT, GL_RGB);
    maskPixels.allocate(CAM_WIDTH, CAM_HEIGHT, OF_PIXELS_RGB);
    maskImage.allocate(CAM_WIDTH, CAM_HEIGHT, OF_IMAGE_COLOR);
    
    // allocate openCv shit
    cvImage.allocate(CAM_WIDTH, CAM_HEIGHT);
    cvMask.allocate(CAM_WIDTH, CAM_HEIGHT);
    cvGrayMask.allocate(CAM_WIDTH, CAM_HEIGHT);
    iplImg = cvImage.getCvImage();
    iplGrayMask = cvGrayMask.getCvImage();
    iplMask = cvMask.getCvImage();
    
    // color of masked part
    maskFill = cvScalarAll(36);
    
    // init post-proc (pixelization pass)
    post.init(CAM_WIDTH, CAM_HEIGHT);
    post.createPass<PixelatePass>();
    
    // load expression classifier(s)
    classifier.load("expressions");
    
    for(int i = 0; i < classifier.size(); i++) {
        if(classifier.getDescription(i) == "smile") cIndex = i;
    }
}

//--------------------------------------------------------------
void ExpressionAnalyzer::update(){
    cam.update();
    
    if(cam.isFrameNew()) {
        cvImage.setFromPixels(cam.getPixels(), CAM_WIDTH, CAM_HEIGHT);
        // apply our mask
        applyMask();
        cvSet(iplImg,maskFill,iplGrayMask);
        if(tracker.update(toCv(cam))) {
            classifier.classify(tracker);
        }
    }
    
    // get face outline
    ofPolyline outline = tracker.getImageFeature(ofxFaceTracker::FACE_OUTLINE);
    
    // draw the outline vertices into an FBO for masking
    maskFbo.begin();
    ofDisableAlphaBlending();
    ofFill();
    ofSetColor(255, 255, 255);
    ofRect(0,0,CAM_WIDTH,CAM_HEIGHT);
    ofSetColor(0,0,0);
    // draw filled polyline
    ofBeginShape();
    for(int i = 0; i < outline.getVertices().size(); i++) {
        ofVertex(outline.getVertices().at(i).x, outline.getVertices().at(i).y);
    }
    ofEndShape();
    maskFbo.end();
    
    maskFbo.readToPixels(maskPixels);
    maskImage.setFromPixels(maskPixels);
}

//--------------------------------------------------------------
void ExpressionAnalyzer::draw(){
    ofSetColor(255);
	cam.draw(0, 0);
	//tracker.draw();
    
    //maskFbo.draw(0,0);
    
    float res = (classifier.getProbability(cIndex) * (300.0f - 20.0f) + 20.0f);
//    ofLogNotice("RES :: " + ofToString(res));
    ofVec2f resVec = ofVec2f(res, res);
    post.getPasses()[0]->setResolution(resVec);
    
    ofSetColor(255,255,255,255);
    
    ofPushMatrix();
    post.begin();
    glTranslated(0, ofGetHeight(), 0);
    glScalef(2, -2, 0);
    cvImage.draw(0,0);
    post.end();
    ofPopMatrix();
    
	int w = 100, h = 12;
	ofPushStyle();
	ofPushMatrix();
	ofTranslate(5, 10);
	int n = classifier.size();
	int primary = classifier.getPrimaryExpression();
    for(int i = 0; i < n; i++){
		ofSetColor(i == primary ? ofColor::red : ofColor::black);
		ofRect(0, 0, w * classifier.getProbability(i) + .5, h);
		ofSetColor(255);
		ofDrawBitmapString(classifier.getDescription(i), 5, 9);
		ofTranslate(0, h + 5);
        
//        ofLogNotice(classifier.getDescription(i) + " :: " + ofToString(classifier.getProbability(i)));
    }
	ofPopMatrix();
	ofPopStyle();
    
	ofDrawBitmapString(ofToString((int) ofGetFrameRate()), ofGetWidth() - 20, ofGetHeight() - 10);
	drawHighlightString(
                        string() +
                        "r - reset\n" +
                        "e - add expression\n" +
                        "a - add sample\n" +
                        "s - save expressions\n"
                        "l - load expressions",
                        14, ofGetHeight() - 7 * 12);

}

void ExpressionAnalyzer::applyMask() {
    cvMask.setFromPixels(maskImage.getPixels(), CAM_WIDTH, CAM_HEIGHT);
    cvInRangeS(iplMask, cvScalarAll(250), cvScalarAll(255), iplGrayMask);
}

//--------------------------------------------------------------
void ExpressionAnalyzer::keyPressed(int key){
    if(key == 'r') {
		tracker.reset();
		classifier.reset();
	}
	if(key == 'e') {
		classifier.addExpression();
	}
	if(key == 'a') {
		classifier.addSample(tracker);
	}
	if(key == 's') {
		classifier.save("expressions");
	}
	if(key == 'l') {
		classifier.load("expressions");
    }
}

//--------------------------------------------------------------
void ExpressionAnalyzer::keyReleased(int key){

}

//--------------------------------------------------------------
void ExpressionAnalyzer::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ExpressionAnalyzer::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ExpressionAnalyzer::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ExpressionAnalyzer::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ExpressionAnalyzer::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ExpressionAnalyzer::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ExpressionAnalyzer::dragEvent(ofDragInfo dragInfo){ 

}
