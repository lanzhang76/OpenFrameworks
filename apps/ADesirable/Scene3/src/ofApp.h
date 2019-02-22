#pragma once
#include "ofMain.h"
#include "ofxBox2d.h"
#include "ofxOsc.h"


// -------------------------------------------------

class ofApp : public ofBaseApp {
    
public:
    
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void resized(int w, int h);
    
    ofxOscReceiver receiver;
    float blink;
    bool blinked;
    
    ofxBox2d                               box2d;

    vector   <shared_ptr<ofxBox2dRect> >   boxes;
    ofxBox2dEdge                            edgeLine;
    
    bool cart, transition;
    
    ofTrueTypeFont chakra11;
    
    ofImage cartImage;
    
//    //bird
//    float targetX, targetY;
//    
//    float x,y;
//    float rightTip,lerping;
//    int direction;
};

