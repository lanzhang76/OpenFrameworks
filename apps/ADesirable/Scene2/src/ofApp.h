#pragma once

#include "ofMain.h"
#include "ofxOsc.h"

#include "banner.hpp"

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
		
    vector<banner> banners;
    
    ofEasyCam cam;

    glm::vec3 camZ,camPos;
    
    ofTrueTypeFont chakra11;
    
    ofxOscReceiver receiver;
    glm::vec3 acc, rotation;
    
    float time;
    
    float x,y;
    float rightTip,lerping;
    int direction;
    float targetX, targetY;
    
};
