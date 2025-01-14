#pragma once

#include "ofMain.h"
#include "Mover.hpp"

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
		
    float x,y;
    float rightTip,lerping;
    int direction;
    float targetX, targetY;
    
    ofTrueTypeFont chakra20;
    ofTrueTypeFont chakra11;
    ofImage end;
    ofImage logo;
    bool explain;
    
    vector<Mover> movers;
};
