#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    DEBUG = true;
    toggleInfo = true;
    maskOn = false;
    
//    width = 500;
//    height = 500;
    
    // TODO: figure out the best image size Ñ this is stretched
    // 800 x 1207?
    width = 1207;//1280;//1545;
    height = 800;//1024;
    
    avgShader.load("", "average.frag");
    avgShader2.load("", "average.frag");
    comboShader.load("", "combineShaders.frag");
    
    makeDirectories();
    loadImages();
    
    breath.setup(width, height);
    mask = breath.blur;
    avg1.allocate(width, height);
    avg2.allocate(width, height);
    fadeFbo.allocate(width, height);
    compositeImage.allocate(width, height);
    
    fading = false;
    
    ofAddListener(breath.breathEnded,this, &ofApp::onBreathEnd);
}

void ofApp::loadImages() {
    for(auto& dir : directories) {
        for (int i= 0; i < dir.size(); i++){
            ofImage temp;
            images.push_back(temp);
            images[images.size()-1].load(dir.getPath(i));
            images[images.size()-1].resize(width, height);
        }
    }
    currImgIndex = 0;
}

void ofApp::makeDirectories() {
    // Match dirNames size with for loop Ñ I was lazy and didn't do variable sheeit
//    string dirNames[11] = {"seqouia", "alps", "desolation", "dv_bw", "henry", "iva_bw", "iva_color",
//        "lost_bw", "lost_color", "ostrander", "saddle"};
//    for(int i = 0; i < 11; i++) {
//        ofDirectory dir;
//        dir.sort();
//        dir.listDir(dirNames[i]);
//        directories.push_back(dir);
//    }
    
    // TESTING Ñ if need speed
    string dirNames[1] = {"seqouia"};
    for(int i = 0; i < 1; i++) {
        ofDirectory dir;
        dir.sort();
        dir.listDir(dirNames[i]);
        directories.push_back(dir);
    }
}

void ofApp::setMask() {
    float time = ofGetElapsedTimef();
    if(!breath.breathing) {
        breath.setBreathe( ofPoint(width / 2, height/2),
                          0.005,
                          0.01, 10, height/2 );
    }
    breath.update();
}

void ofApp::fade() {
    if(fadeColor == 256) {
        fading = false;
        currImgIndex++;
        currImgIndex %= images.size();
    } else {
        fadeFbo.begin();
        ofClear(0);
        ofBackground(fadeColor);
        fadeFbo.end();
        fadeColor++;
    }
}

void ofApp::initFade() {
    fadeColor = 0;
    fading = true;
}

void ofApp::makeAverages(ofFbo& fbo, ofShader& shader, int shift, bool focus) {
    fbo.begin();
    ofClear(0);
    shader.begin();
    shader.setUniform1f("imgTotal", compositeTotal);
    shader.setUniform1f("focus", focus);
    shader.setUniform1f("fading", fading);
    if(fading) shader.setUniformTexture("mask", fadeFbo.getTexture(), 0);
    else shader.setUniformTexture("mask", mask.getTextureReference(), 0);
    for(int i = 0; i < textureTotal; i++) {
        int index = shift+i;
        index %= images.size();
        shader.setUniformTexture("tex" + std::to_string(i+1), images[index], i+1);
    }
    if(fading) fadeFbo.draw(0,0);
    else mask.draw();
    shader.end();
    fbo.end();
}

void ofApp::makeComposite(ofFbo fbo1, ofFbo fbo2) {
    compositeImage.begin();
    ofClear(0);
    comboShader.begin();
    
    comboShader.setUniformTexture("tex1", fbo1.getTexture(), 0);
    comboShader.setUniformTexture("tex2", fbo2.getTexture(), 1);
    fbo1.draw(0,0);
    comboShader.end();
    compositeImage.end();
}

//--------------------------------------------------------------
void ofApp::update(){
    if(fading) fade();
    else setMask();
    makeAverages(avg1, avgShader, currImgIndex, true);
    makeAverages(avg2, avgShader2, currImgIndex + 15, false);
    makeComposite(avg1, avg2);
}

//--------------------------------------------------------------
void ofApp::draw(){
    compositeImage.draw(0,0);
    
    if (DEBUG) {
        if(maskOn) {
            mask.draw();
        }
        if(toggleInfo) {
            ofDrawBitmapString(ofToString(ofGetFrameRate()), 30, 30);
            ofDrawBitmapString("Fading: " + ofToString(fading), 30, 50);
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(DEBUG){
        if( key == ' ') breath.animating = !breath.animating;
        if(key == 'f') initFade();
        if(key == 't') toggleInfo = !toggleInfo;
        if(key == 'm') maskOn = !maskOn;
    }
}

void ofApp::onBreathEnd(float &tEnded) {
    initFade();
}








//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
