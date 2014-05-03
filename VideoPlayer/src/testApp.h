#pragma once

#include "ofMain.h"
#include "FutureVideo.h"
#include "Arduino.h"
#include "AppEvent.h"

#define NUM_VIDEOS 3

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
    
        void onButtonPressed(int &btnIndex);

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
        static FutureVideo *videos[NUM_VIDEOS];
    
        Arduino *arduino;
};
