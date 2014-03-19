#pragma once

#define STRINGIFY(A) #A

#include "ofMain.h"
#include "ofFbo.h"
#include "ofVec3f.h"
#include "ofShader.h"

class Pixelate {
public:
    Pixelate(int w, int h);
    
    virtual void setup();
    virtual void begin();
    virtual void end();
    virtual void update();
    virtual void draw(int x, int y);
    
    void setResolution(ofVec2f res);
    
protected:
    int w, h;
    
    void texturedQuad(float x, float y, float width, float height, float s = 1.0, float t = 1.0);
    
    ofVec2f resolution;
    
    ofShader shader;
    ofFbo readFbo;
    ofFbo writeFbo;
};
