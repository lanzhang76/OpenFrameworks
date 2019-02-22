#include "ofApp.h"



//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(220);
    ofSetFrameRate(60);
    
    chakra11.load("Chakra.ttf",11, true,true);
    
    //set up parameters
    rightTip = 0;
    lerping = 0.02;
    direction = 1;
    
    plane.set(500,500,20,20);
    plane.tiltDeg(90);
//    plane.rollDeg(45);
    plane.setPosition(0,300,0);
    
    PlaneColor = ofColor(200);
    
    //BOOLEANS
    reachDot = FALSE;
    successString = false;
    startString = true;
    
    
//    cam.setPosition(0, 100, 400);
    
    const int RECEIVE_PORT   = 7000;
    receiver.setup(RECEIVE_PORT);
 
//    targetY = 600; //600
    dotSize=0.1;
    dotPos = glm::vec3 (ofGetWidth()*.5,600,0);

}

//--------------------------------------------------------------
void ofApp::update(){
    
    targetX = 300;
    targetY = 600;
    x += (targetX - x) * lerping;
    y += ((targetY - y) * lerping) - 0.5*direction;
    rightTip += 2*direction;
    
    if (rightTip > 120 || rightTip < -40) {
        direction = -direction;
    }
    
    ofMesh& mesh = plane.getMesh();
    
    for (int i=0; i<mesh.getVertices().size(); i++)
    {
        glm::vec3& vertex = mesh.getVertices()[i];
        
        float time = ofGetElapsedTimef();
        float noise =
        ofSignedNoise ( vertex.x * 0.02,    // x pos
                       vertex.y * 0.04,    // y pos
                       time * 1.1   // time (z) to animate
                       );

        vertex.z = noise * 10;
        
    }
    
    //box
    dot.panDeg(1);
    dot.tiltDeg(1);
    
    if (reachDot){
        PlaneColor = ofColor(220,85,75);
    } else {
        PlaneColor = ofColor(200);
    }
    
    //osc
    ofxOscMessage m;
    
    while(receiver.hasWaitingMessages()){
        receiver.getNextMessage(m);
        if (m.getAddress() == "Muse-2C07/elements/alpha_relative"){
            //        cout << "getting alpha" <<endl;
            alpha = m.getArgAsFloat(1);
            alphaTrans = ofMap(alpha, 0,0.4,1,100);
            if (alphaTrans != alphaStorage[(index - 1 + store)/store]){
                alphaStorage[index] = alphaTrans;
                index = (index + 1) % store;
            }
            alphaMean =
            (alphaStorage[0]+alphaStorage[1]+alphaStorage[2]+alphaStorage[3]+alphaStorage[4])*0.2;
            

            
//            if(targetY <= 50){
//                targetY = 50;
//            } else if (targetY > 50){
            
            if(dotPos.y > 140){
                increment = 0.017;//0.05
                SizeIncrement = 0.004;
//                targetY -= (100-alphaMean)* increment;
//                targetY = targetY;
                dotPos.y -= (100-alphaMean)* increment;
                dotPos.y = dotPos.y;
                dotSize += (60-alphaMean)*SizeIncrement;
                dotSize = dotSize;
                dot.set(dotSize);
                dot.setPosition(dotPos.x,dotPos.y,0);
                
                cout << int(50-alphaMean) << endl;
            } else if (dotPos.y <= 140) {
                reachDot = true;
                successString = true;
                startString = false;
                dotPos.y = 140;
            }
  
        
        }
    }
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
   
    ofSetColor(40);
//    ofDrawBitmapString("alphaVal: " + ofToString(alphaMean),20,20);
//    ofDrawBitmapString("Arousal Level: " + ofToString(80 - alphaMean),20,40);
//    ofDrawBitmapString("targetY: " + ofToString(targetY),20,60);
    
   
    ofPushMatrix();
    cam.begin();
//    ofDrawAxis(100);
    ofSetColor(110);
    plane.drawVertices();
    ofSetColor(PlaneColor);
    plane.drawWireframe();
   cam.end();
    ofPopMatrix();
    
    
    ofPushStyle();
    ofSetColor(40);
    ofNoFill();
    ofDrawTriangle(x-80, y-30,          x-74, y-15,   x-100, y-20);  // head
    ofDrawTriangle(x-30, y+rightTip-5,  x+50, y+50,   x-50, y+50);  // up wing
    ofDrawTriangle(x-50, y+50,          x-33, y+33,   x-80, y-30);  // neck
    ofDrawTriangle(x, y,                x+50, y+50,   x-50, y+50);  // body
    ofDrawTriangle(x+50, y+50,          x+30, y+30,   x+100, y-20);  // tail
    ofDrawTriangle(x+40, y+rightTip,    x+50, y+50,   x-50, y+50);  // down wing
    ofPopStyle();
    
    ofPushMatrix();
//    cam.begin();
    ofSetColor(220,85,75);
    ofNoFill();
    dot.drawWireframe();
//    ofDrawBox(dotPos,10);
//    cam.end();
    ofPopMatrix();

    ofPushStyle();
    ofSetColor(80);
    if (successString){
        chakra11.drawString("Your desire has been uploaded as targeting data to the cloud network.",74,ofGetHeight()-340);
    }
    
    if (startString){
//        chakra11.drawString("Think of the red dot as something that you want.",140,35);
//        chakra11.drawString("(your EEG data will determine your speed)",150,55);
        chakra11.drawString("Think of something you desire. The red dot grows and rises as you think harder.",40,ofGetHeight()-80);
    }
    ofPopStyle();
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if (key == OF_KEY_RETURN && y-dotPos.y <= 0){
        reachDot = true;
        successString = true;
        startString = false;
    }

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
//    targetY = 600;
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
