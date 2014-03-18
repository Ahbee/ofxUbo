#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofDisableArbTex();
    shader.load("shader");
    shader.printLayout("SwirlSettings");
    
    flowerImage.loadImage("flowers.jpg");
    
    gui.setup();
    gui.add(centerX.setup("Center X", 0.5, 0.0, 1.0));
    gui.add(centerY.setup("Center Y",0.5, 0.0, 1.0));
    gui.add(radius.setup("Radius", 0.3, 0.2, 0.5));
    gui.add(angle.setup("Angle", 1, -1.0, 1.0));
}

//--------------------------------------------------------------
void ofApp::update(){
    swirlSettings.radius = radius;
    swirlSettings.angle = angle;
    swirlSettings.center = ofVec2f(centerX,centerY);
}

//--------------------------------------------------------------
void ofApp::draw(){
    shader.begin();
    shader.setUniformBuffer("SwirlSettings", swirlSettings);
    shader.setUniformTexture("tex", flowerImage.getTextureReference(), 0);
    ofDrawPlane(ofGetWidth()/2.0, ofGetHeight()/2.0, ofGetWidth(), ofGetHeight());
    shader.end();
    
    gui.draw();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
