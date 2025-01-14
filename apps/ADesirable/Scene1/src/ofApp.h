#pragma once

#include "ofMain.h"
#include "ofxOsc.h"

#define store 5

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
		
    ofxOscReceiver receiver;
    float alpha, alphaTrans,alphaMean;
    float alphaStorage[store];
    int index = 0;
    
    float difference, increment;
    float targetX, targetY;
    
    float x,y;
    float rightTip,lerping;
    int direction;
    
    ofPlanePrimitive plane;
    ofEasyCam cam;
    
    ofBoxPrimitive dot;
    glm::vec3 dotPos;
    float dotSize;
    float SizeIncrement;
    
    ofColor PlaneColor;
    ofTrueTypeFont chakra11;
    bool reachDot;
    bool successString;
    bool startString;
    
};
