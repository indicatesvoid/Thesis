#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    arduino = new Arduino();
    
    for(size_t idx=0; idx < NUM_VIDEOS; idx++) videos[idx]->load();
    
    ofAddListener(AppEvent::BUTTON_PRESSED, this, &testApp::onButtonPressed);
}

//--------------------------------------------------------------
void testApp::update(){
    arduino->update();
    
    for(size_t idx=0; idx < NUM_VIDEOS; idx++) videos[idx]->update();
}

//--------------------------------------------------------------
void testApp::draw(){
    for(size_t idx=0; idx < NUM_VIDEOS; idx++) {
        videos[idx]->draw();
    }
}

void testApp::onButtonPressed(int &btnIndex) {
    for(size_t idx=0; idx < NUM_VIDEOS; idx++) {
        bool active = (idx == btnIndex) ? true : false;
        videos[idx]->setActive(active);
    }
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
