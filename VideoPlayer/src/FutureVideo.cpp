//
//  FutureVideo.cpp
//  VideoPlayer
//
//  Created by William Clark on 4/26/14.
//
//

#include "FutureVideo.h"

FutureVideo::FutureVideo(string _path, bool _active) {
    this->sPath = _path;
    this->bIsActive = _active;
}

void FutureVideo::setActive(bool active) {
    bIsActive = active;
    
    if(!active) {
	player.close();
        player.stop();
        player.firstFrame();
    }
    
    if(active) {
	player.loadMovie(sPath);
        play();
    }
}

void FutureVideo::load() {
    player.loadMovie(sPath);
    play();
}

void FutureVideo::update() {
    if(bIsActive) {
	if(player.getIsMovieDone()) player.firstFrame();
	player.update();
    }
}

void FutureVideo::play() {
    if(bIsActive) player.play();
}

void FutureVideo::draw() {
    if(bIsActive) player.draw(0,0,ofGetWidth(),ofGetHeight());
}


