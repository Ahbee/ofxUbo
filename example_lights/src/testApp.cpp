#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofEnableDepthTest();
    ofDisableArbTex();
    
    //set initial camera position
    easyCam.setPosition(500, 100, 100);
    easyCam.lookAt(ofVec3f(0,0,0));
    
    // load shaders
    shader.load("shader");
    shader2.load("shader2");
    
    //print layouts
    shader.printLayout("Material");
    shader.printLayout("Light");
    shader.printLayout("NormalMatrix");
    
    //load wood Image
    woodImage.loadImage("wood.jpg");
    
    // set Light Nodes in intial position
    lightNode1.setPosition(0, 20, 140);
    lightNode2.setPosition(40, 20, -50);
    
    // set primitives in position
    plane.set(500,500);
    plane.rotate(-90, ofVec3f(1,0,0));
    sphere.setPosition(0, 50, 0);
    cone.setPosition(-100, cone.getHeight()/2.0, 10);
    cone.rotate(180, 1, 0, 0);
    cone.setResolution(20, 20, 20);
    cube.setPosition(100, 50, 200);
    cube.setScale(.5);
    
    // set up tween to move light2 up and down
    up.setParameters(1, easeLinear, ofxTween::easeIn, 20, 100, 4000, 0.0);
    ofAddListener(up.end_E, this, &testApp::upCompleted);
    ofAddListener(down.end_E, this, &testApp::downCompleted);
    // create Materials
    blue.diffuseColor = ofVec4f(0.1, 0.1, 0.8, 1.0);
    blue.specularColor = ofVec4f(0.8, 0.8, 0.8, 1.0);
    blue.specularShininess = 0.1;
    
    gold.diffuseColor = ofVec4f(0.803f, 0.709f, 0.15f, 1.0f);
    gold.specularColor = ofVec4f(0.803f, 0.709f, 0.15f, 1.0f) * 0.75;
    gold.specularShininess = 0.18;
    
    grey.diffuseColor = ofVec4f(0.4, 0.4, 0.4, 1.0);
    grey.specularColor = ofVec4f(0.95f, 0.95f, 0.95f, 1.0f);
    grey.specularShininess = .3;
    
    // Set up Lighting
    light.lightAttenuation = 1/500.0;
    light.ambientIntensity = ofVec4f(.2, .2, .2, 1.0);
    light.lights[0].lightIntensity = ofVec4f(.8, .8, .8, 1.0);
    light.lights[1].lightIntensity = ofVec4f(.8, .8, .8, 1.0);
}

//--------------------------------------------------------------
void testApp::update(){
    // update lightNode position
    lightNode1.rotateAround(.8, ofVec3f(0,1,0), ofVec3f(0,0,0));
    if (up.isRunning()) {
        lightNode2.setPosition(lightNode2.getX(), up.update(), lightNode2.getZ());
    }else if (down.isRunning()){
        lightNode2.setPosition(lightNode2.getX(), down.update(), lightNode2.getZ());
    }
    
    // update Lighting
    ofVec3f light1CamSpacePos = lightNode1.getPosition() * (easyCam.getModelViewMatrix());
    ofVec3f light2CamSpacePos = lightNode2.getPosition() * (easyCam.getModelViewMatrix());
    light.lights[0].cameraSpaceLightPos = light1CamSpacePos;
    light.lights[1].cameraSpaceLightPos = light2CamSpacePos;
    
    // rotate cube
    cube.rotate(1, ofVec3f(1,0,0));
}

//--------------------------------------------------------------
void testApp::draw(){
    ofBackground(0);
    
    easyCam.begin();
    
    shader.begin();
    shader.setUniformBuffer("Light", light);
    //draw plane
    shader.setUniformBuffer("Material", blue);
    shader.setUniformBuffer("NormalMatrix", calcNormalMatrix(plane.getGlobalTransformMatrix() * easyCam.getModelViewMatrix()));
    plane.draw();
    // draw sphere
    shader.setUniformBuffer("Material", gold);
    shader.setUniformBuffer("NormalMatrix", calcNormalMatrix(sphere.getGlobalTransformMatrix() * easyCam.getModelViewMatrix()));
    sphere.draw();
    // draw cone
    shader.setUniformBuffer("Material", grey);
    shader.setUniformBuffer("NormalMatrix", calcNormalMatrix(cone.getGlobalTransformMatrix()*easyCam.getModelViewMatrix()));
    cone.draw();
    shader.end();
    //draw box;
    shader2.begin();
    shader2.setUniformBuffer("Light", light);
    shader2.setUniformBuffer("Material", blue);
    shader2.setUniformBuffer("NormalMatrix", calcNormalMatrix(cube.getGlobalTransformMatrix()*easyCam.getModelViewMatrix()));
    shader2.setUniformTexture("tex0", woodImage.getTextureReference(), 0);
    cube.draw();
    shader2.end();
    
    // draw light nodes
    lightNode2.draw();
    lightNode1.draw();
    
    easyCam.end();

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

ofMatrix3x3 testApp::calcNormalMatrix(ofMatrix4x4 matrix){
    ofMatrix3x3 normalMat(matrix._mat[0].x,matrix._mat[0].y,matrix._mat[0].z,
                          matrix._mat[1].x,matrix._mat[1].y,matrix._mat[1].z,
                          matrix._mat[2].x,matrix._mat[2].y,matrix._mat[2].z);
    normalMat.invert();
    normalMat.transpose();
    return normalMat;
}

//--------------------------------------------------------------

void testApp::upCompleted(int &n){
    down.setParameters(2, easeLinear, ofxTween::easeIn, 100, 20, 4000, 0.0);
}

void testApp::downCompleted(int &n){
    up.setParameters(1, easeLinear, ofxTween::easeIn, 20, 100, 4000, 0.0);
    
}
