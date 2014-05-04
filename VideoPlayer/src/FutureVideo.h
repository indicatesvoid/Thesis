//
//  FutureVideo.h
//  VideoPlayer
//
//  Created by William Clark on 4/26/14.
//
//

#ifndef __VideoPlayer__FutureVideo__
#define __VideoPlayer__FutureVideo__

#include "ofMain.h"

class FutureVideo {
public:
    FutureVideo(string _path, bool _active = false);
    
    void setActive(bool active);
    bool isActive() { return bIsActive; }
    void load();
    void update();
    void play();
    void draw();
private:
    ofVideoPlayer   player;
    string          sPath;
    bool            bIsActive;
};

#endif /* defined(__VideoPlayer__FutureVideo__) */
