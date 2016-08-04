#pragma once

#include "ofMain.h"
#include "Breath.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
    
    void makeDirectories();
    void loadImages();
    
    void setMask();
    
    void fade();
    void initFade();
    
    void makeAverages(ofFbo& fbo, ofShader& shader, int shift, bool focus);
    void makeComposite(ofFbo fbo1, ofFbo fbo2);
    
    void onBreathEnd(float &tEnded);
    
    bool DEBUG;
    bool toggleInfo;
    bool maskOn;
    
    int width;
    int height;
    
    ofFbo avg1;
    ofFbo avg2;
    ofShader avgShader;
    ofShader avgShader2;
    
    ofShader comboShader;
    
    vector < ofImage > images;
    
    Breath breath;
    
    ofFbo fadeFbo;
    bool fading;
    int fadeColor;
    
    ofxBlur mask;
    ofFbo compositeImage;
    
    int compositeTotal = 29;//29;
    int textureTotal = 15;
    vector<ofDirectory> directories;
    int currImgIndex;
};
