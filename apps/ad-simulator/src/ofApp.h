#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxOpenCV.h"
#include "ofxCv.h"

#include "CTA.hpp"

using namespace cv;
using namespace ofxCv;

#define store 5

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
    
        void randomize(ofRectangle & viewport);
        void randomizeViewports();
        void drawViewportOutline(const ofRectangle & viewport);

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
    //osc
    ofxOscReceiver receiver;
    float alpha, alphaTrans,alphaMean;
    float alphaStorage[store];
    int index = 0;
    glm::vec3 acc,rotation;
    float blink;
    String blinkVal;
    
    //text
    ofTrueTypeFont    verdana30;
    ofTrueTypeFont    verdana14;
    ofTrueTypeFont    Chakra60;
    bool bFirst;
    string typeStr;
    
    //camera capture
    ofVideoGrabber cam;
    ofxCv::ObjectFinder finder;
    
    //image objects
    ofImage ketchup;
    ofImage lip;
    
    //3d view
    ofRectangle viewport3D;
    ofEasyCam camera;
		
    
    //banners
    vector<CTA> banners;
};
