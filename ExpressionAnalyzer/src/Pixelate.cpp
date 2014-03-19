//
//  Pixelate.cpp
//  ExpressionAnalyzer
//
//  Created by William Clark on 3/18/14.
//
//

#include "Pixelate.h"

Pixelate::Pixelate(int w, int h) {
    this->resolution = ofVec2f(100.0f, 100.0f);
    this->w = w;
    this->h = h;
}

void Pixelate::setup() {
    // set fbo settings
    ofFbo::Settings s;
    
    s.width = ofNextPow2(w);
    s.height = ofNextPow2(h);
    s.textureTarget = GL_TEXTURE_2D;
    
    s.useDepth = true;
    s.depthStencilInternalFormat = GL_DEPTH_COMPONENT24;
    s.depthStencilAsTexture = true;
    
    // allocate fbos
//    readFbo.allocate(w, h, GL_RGB);
//    writeFbo.allocate(w, h, GL_RGB);
    readFbo.allocate(s);
    writeFbo.allocate(s);
    
    
    
    readFbo.begin();
    ofClear(255,255,255, 0);
    readFbo.end();
    
    writeFbo.begin();
    ofClear(255,255,255,0);
    writeFbo.end();
    
    // setup shader
    string fragShaderSrc = STRINGIFY(
                                     uniform sampler2D tex;
                                     uniform float xPixels;
                                     uniform float yPixels;
                                     
                                     void main()
                                     {
                                         vec2 texCoords = vec2(floor(gl_TexCoord[0].s * xPixels) / xPixels, floor(gl_TexCoord[0].t * yPixels) / yPixels);
                                         gl_FragColor = texture2D(tex, texCoords);
                                     }
                                     );
    
    shader.setupShaderFromSource(GL_FRAGMENT_SHADER, fragShaderSrc);
    shader.linkProgram();
    
//    shader.load("shaders/component.frag");
}

void Pixelate::begin() {
//    glMatrixMode(GL_PROJECTION);
//    glPushMatrix();
//    
//    glMatrixMode(GL_MODELVIEW);
//    glPushMatrix();
//    
//    glViewport(0, 0, w, h);
//    
//    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
//    
//    ofPushStyle();
//    glPushAttrib(GL_ENABLE_BIT);
    
    readFbo.begin();
}

void Pixelate::end() {
    readFbo.end();
    update();
    
//    glPopAttrib();
//    ofPopStyle();
//    
//    glViewport(0, 0, ofGetWidth(), ofGetHeight());
//    
//    glMatrixMode(GL_PROJECTION);
//    glPopMatrix();
//    
//    glMatrixMode(GL_MODELVIEW);
//    glPopMatrix();
    
//    ofPushStyle();
//    glPushAttrib(GL_ENABLE_BIT);
//    glDisable(GL_LIGHTING);
//    ofSetColor(255, 255, 255);
//    process();
//    if (autoDraw) draw();
//    glPopAttrib();
//    ofPopStyle();
}

void Pixelate::update() {
    writeFbo.begin();
    
    shader.begin();
    shader.setUniformTexture("tex", readFbo.getTextureReference(), 0);
    shader.setUniform1f("xPixels", resolution.x);
    shader.setUniform1f("yPixels", resolution.y);
//    texturedQuad(0, 0, writeFbo.getWidth(), writeFbo.getHeight());
    readFbo.draw(0,0);
    shader.end();
    writeFbo.end();
}

void Pixelate::draw(int x, int y) {
    writeFbo.draw(x, y);
}

void Pixelate::setResolution(ofVec2f res) {
    this->resolution = res;
}

/** PRIVATE **/
void Pixelate::texturedQuad(float x, float y, float width, float height, float s, float t)
{
    // TODO: change to triangle fan/strip
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(x, y, 0);
    
    glTexCoord2f(s, 0);
    glVertex3f(x + width, y, 0);
    
    glTexCoord2f(s, t);
    glVertex3f(x + width, y + height, 0);
    
    glTexCoord2f(0, t);
    glVertex3f(x, y + height, 0);
    glEnd();
}