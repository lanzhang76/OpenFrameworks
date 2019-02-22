#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground (220);
    ofSetFrameRate(60);
    ofSetRectMode(OF_RECTMODE_CENTER);
    chakra11.load("Chakra.ttf",11, true,true);
    
    const int RECEIVE_PORT   = 7000;
    receiver.setup(RECEIVE_PORT);
    
    
    for (int i = 0; i < banners.size(); i++){
        banners[i].setup();
    }
    
    //set up bird
    rightTip = 0;
    lerping = 0.02;
    direction = 1;
}

//--------------------------------------------------------------
void ofApp::update(){
    targetX = mouseX;
    targetY = mouseY;
    x += (targetX - x) * lerping;
    y += ((targetY - y) * lerping) - 0.5*direction;
    rightTip += 2*direction;
    
    if (rightTip > 120 || rightTip < -40) {
        direction = -direction;
    }
   
    for(int i = 0; i < banners.size(); i ++){
        banners[i].update();
    }
   
    time = ofGetFrameNum();
    if(ofGetFrameNum() % 20 == 0){
        int MaxNum = 1;
        for(int i = 0; i < MaxNum; i ++){
            banner oneBanner;
            oneBanner.setup();
            banners.push_back(oneBanner);
        }
    }
    
    ofxOscMessage m;
    
    while(receiver.hasWaitingMessages()){
        receiver.getNextMessage(m);
        if (m.getAddress() == "Muse-2C07/acc"){
            acc.x = m.getArgAsFloat(0);
            acc.y = m.getArgAsFloat(1);
            acc.z = m.getArgAsFloat(2);

//            cout << acc.y <<endl;
            
            rotation.x = ofMap(acc.x,-1,1,0.1,-0.1);
            rotation.y = ofMap(acc.y,-1,1,0.1,-0.1);
            rotation.z = ofMap(acc.z,-1,1,0.08,-0.08);

           

        }
        
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
   
//    ofDrawBitmapString(ofToString(time/1000),20,20);
//    ofDrawBitmapString("Z-cam: " + ofToString(camZ),20,20);
//    ofDrawBitmapString("camPos " + ofToString(camPos),20,40);
    
    ofPushMatrix();
    ofPushStyle();
     cam.begin();
    ofEnableDepthTest();
//        ofDrawAxis(200);
    cam.tilt(rotation.x);
    cam.pan(rotation.y);
//    cam.roll(rotation.z);
    
    for(int i = 0; i < banners.size(); i ++){
        banners[i].draw();
    }
    
    ofDisableDepthTest();
    cam.end();
    ofPopStyle();
    ofPopMatrix();
    
    ofPushMatrix();
    ofPushStyle();
        ofSetColor(80);
        ofNoFill();
        ofDrawTriangle(x-80, y-30,          x-74, y-15,   x-100, y-20);  // head
        ofDrawTriangle(x-30, y+rightTip-5,  x+50, y+50,   x-50, y+50);  // up wing
        ofDrawTriangle(x-50, y+50,          x-33, y+33,   x-80, y-30);  // neck
        ofDrawTriangle(x, y,                x+50, y+50,   x-50, y+50);  // body
        ofDrawTriangle(x+50, y+50,          x+30, y+30,   x+100, y-20);  // tail
        ofDrawTriangle(x+40, y+rightTip,    x+50, y+50,   x-50, y+50);  // down wing
    ofPopStyle();
    ofPopMatrix();

    
    ofSetColor(80);
//    ofDrawBitmapStringHighlight("rotation: " + ofToString(rotation), 25, 120);
//    chakra11.drawString("Browse around. You see your desire everywhere.", 145,35);
//    chakra11.drawString("(tilt your head to adjust the viewpoint)", 160,55);
    //Browse around(tilt your head). //Your desire is camouflaged as banner ads, constantly being generated to infiltrate your online experience
    
    chakra11.drawString("Browse around (tilt your head).", 200,ofGetHeight()-80);
    chakra11.drawString("Your desire is camouflaged as banner ads, constantly ", 120,ofGetHeight()-60);
     chakra11.drawString("being generated to infiltrate your online experience", 124,ofGetHeight()-40);

}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
   
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
