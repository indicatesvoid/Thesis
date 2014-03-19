#include "Mask.h"

Mask::Mask(int w, int h, bool alphaMask) {
    this->w = w;
    this->h = h;
    this->alphaMask = alphaMask;
    
    // color of masked part
    this->maskFill = cvScalarAll(0);
}

void Mask::setup() {
    allocate();
    
    // setup alpha mask shader
    if(alphaMask) {
        maskShader.load("shaders/composite");
        
        alphaMaskImage.allocate(w,h, OF_IMAGE_GRAYSCALE);
        topLayer.allocate(w, h, OF_IMAGE_COLOR);
    }
}

void Mask::allocate() {
    // allocate FBOs for mask and pixelface
    maskFbo.allocate(w, h, GL_RGB);
    maskPixels.allocate(w, h, OF_PIXELS_RGB);
    maskImage.allocate(w, h, OF_IMAGE_COLOR);
    
    // clear FBOs
    maskFbo.begin();
    ofClear(255,255,255, 0);
    maskFbo.end();
    
    // allocate openCv shit
    cvImage.allocate(w, h);
    cvMask.allocate(w, h);
    cvGrayMask.allocate(w, h);
    iplImg = cvImage.getCvImage();
    iplGrayMask = cvGrayMask.getCvImage();
    iplMask = cvMask.getCvImage();
}

void Mask::updateMask(const unsigned char *pixels) {
    cvImage.setFromPixels(pixels, w, h);
    cvMask.setFromPixels(maskImage.getPixels(), w, h);
    cvInRangeS(iplMask, cvScalarAll(250), cvScalarAll(255), iplGrayMask);
    
    cvSet(iplImg,maskFill,iplGrayMask);
    
    if(alphaMask) {
        topLayer.setFromPixels(pixels, w, h, OF_IMAGE_COLOR);
        alphaMaskImage.setFromPixels(cvMask.getPixels(), w, h, OF_IMAGE_COLOR);
        maskShader.begin();
        maskShader.setUniformTexture("Tex0", topLayer.getTextureReference(), 0);
        maskShader.setUniformTexture("Tex1", alphaMaskImage.getTextureReference(), 1);
        maskShader.end();
    }
}

//void Mask::updateMask(const unsigned char *maskPixels, ofImage top) {
//    if(!alphaMask) return;
//    
//    updateMask(maskPixels);
//    
//    topLayer.clone(top);
////    alphaMaskImage.clone(mask);
//    alphaMaskImage.setFromPixels(cvImage.getPixels(), w, h, OF_IMAGE_GRAYSCALE);
//    
//    maskShader.begin();
//    maskShader.setUniformTexture("Tex0", topLayer.getTextureReference(), 0);
//    maskShader.setUniformTexture("Tex1", alphaMaskImage.getTextureReference(), 1);
//    maskShader.end();
//}

void Mask::begin() {
    maskFbo.begin();
}

void Mask::end() {
    maskFbo.end();
    
    maskFbo.readToPixels(maskPixels);
    maskImage.setFromPixels(maskPixels);
}

void Mask::draw(int x, int y) {
    if(alphaMask) {
//        topLayer.draw(x,y);
//        alphaMaskImage.draw(x,y);
        
        maskShader.begin();
        ofEnableAlphaBlending();
        glActiveTexture(GL_TEXTURE0_ARB);
        topLayer.getTextureReference().bind();
        
        glActiveTexture(GL_TEXTURE1_ARB);
        alphaMaskImage.getTextureReference().bind();
        //draw a quad the size of the frame
        glBegin(GL_QUADS);
        glMultiTexCoord2d(GL_TEXTURE0_ARB, 0, 0);
        glMultiTexCoord2d(GL_TEXTURE1_ARB, 0, 0);
        glVertex2f( 0, 0);
        
        glMultiTexCoord2d(GL_TEXTURE0_ARB, topLayer.getWidth(), 0);
        glMultiTexCoord2d(GL_TEXTURE1_ARB, alphaMaskImage.getWidth(), 0);
        glVertex2f( ofGetWidth(), 0);
        
        glMultiTexCoord2d(GL_TEXTURE0_ARB, topLayer.getWidth(), topLayer.getHeight());
        glMultiTexCoord2d(GL_TEXTURE1_ARB, alphaMaskImage.getWidth(), alphaMaskImage.getHeight());
        glVertex2f( ofGetWidth(), ofGetHeight());
        
        glMultiTexCoord2d(GL_TEXTURE0_ARB, 0, topLayer.getHeight());
        glMultiTexCoord2d(GL_TEXTURE1_ARB, 0, alphaMaskImage.getHeight());
        glVertex2f( 0, ofGetHeight());
        glEnd();
        
        //deactive and clean up
        glActiveTexture(GL_TEXTURE1_ARB);
        alphaMaskImage.getTextureReference().unbind();
        
        glActiveTexture(GL_TEXTURE0_ARB);
        topLayer.getTextureReference().unbind();
        maskShader.end();
    }
    
    else cvImage.draw(x,y);
}

void Mask::drawMask(int x, int y) {
    maskImage.draw(0,0);
}