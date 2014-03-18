#pragma once

#include "ofMain.h"
#include "ofxUbo.h"
#include "ofxTween.h"

struct Material {
    ofVec4f diffuseColor;
    ofVec4f specularColor;
    float specularShininess;
};

struct PerLight {
    ofVec3f cameraSpaceLightPos;
    ofVec4f lightIntensity;
};

struct Light {
    ofVec4f ambientIntensity;
    float lightAttenuation;
    PerLight lights[2];
};


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    ofMatrix3x3 calcNormalMatrix(ofMatrix4x4 matrix);
    void upCompleted(int &n);
    void downCompleted(int &n);
    
    ofxUboShader shader;
    ofxUboShader shader2; // this shader uses a texture
    ofEasyCam easyCam;
    
    ofNode lightNode1;
    ofNode lightNode2;
    Light light;
    
    Material blue;
    Material gold;
    Material grey;
    ofImage woodImage;
    
    ofPlanePrimitive plane;
    ofSpherePrimitive sphere;
    ofConePrimitive cone;
    ofBoxPrimitive cube;
    
    ofxTween up;
    ofxTween down;
    ofxEasingLinear easeLinear;
		
};
