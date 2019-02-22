#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxXmlSettings.h"
#include "Plane.hpp"

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
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
    ofEasyCam cam;
    
//    ofMesh mesh;
    Plane mesh;
    
    ofxPanel gui;
    ofParameter<float> scale;
    ofParameter<glm::vec3> pos;
    ofParameter<int> mode;
//    ofParameter<float> noiseAmp;
//    ofParameter<float> noiseFreq;
//    ofParameter<glm::vec2> noiseScale;
//    ofParameter<ofColor> colorNear,colorFar;
    
    ofBoxPrimitive box;
};
