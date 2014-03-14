#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
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
void testApp::update(){
    swirlSettings.radius = radius;
    swirlSettings.angle = angle;
    swirlSettings.center = ofVec2f(centerX,centerY);
}

//--------------------------------------------------------------
void testApp::draw(){
    shader.begin();
    shader.setUniformBuffer("SwirlSettings", swirlSettings);
    shader.setUniformTexture("tex", flowerImage.getTextureReference(), 0);
    ofDrawPlane(ofGetWidth()/2.0, ofGetHeight()/2.0, ofGetWidth(), ofGetHeight());
    shader.end();
    
    gui.draw();

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
