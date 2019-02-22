#pragma once

#include "ofMain.h"
#include "ofxLeapMotion2.h"

#include "Mover.hpp"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
	
    void keyPressed  (int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    void exit();
    
	ofxLeapMotion leap;
	vector <ofxLeapMotionSimpleHand> simpleHands;
    
    ofEasyCam cam;
    
    ofPoint handPos;
    
    float x,y;
    float rightTip,lerping;
    int direction;
    float targetX, targetY;
    
    ofBoxPrimitive dot;
    glm::vec3 dotPos;
    
    ofTrueTypeFont chakra20;
    ofTrueTypeFont chakra11;
    
    ofImage end;
    
    bool yee;
    
    vector<Mover> movers;
};
