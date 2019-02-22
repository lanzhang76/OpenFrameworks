#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(220);
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofSetFrameRate(60);
    
    //set up bird
    rightTip = 0;
    lerping = 0.02;
    direction = 1;
    //
    
    chakra20.load("Chakra.ttf",20,true,true);
    chakra11.load("Chakra.ttf",11,true,true);
    end.load("end-08.png");
    logo.load("logo-09.png");
    
    //movers
    ofSetCircleResolution(80);
    for (int y=0; y<16; y++) {
        for (int x=0; x<12; x++) {
            float posX = ofMap(x, 0, 11, 0, 600);
            float posY = ofMap(y, 0, 15, 0, 800);
            Mover mover( glm::vec2(posX, posY) );
            mover.mass = ofRandom(2,7);
            movers.push_back(mover);
        }
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    
    targetX = ofGetMouseX();
    targetY = ofGetMouseY();
    x += (targetX - x);// * lerping;
    y += (targetY - y);// * lerping) - 0.5*direction;
    
    rightTip += 2*direction;
    
    if (rightTip > 120 || rightTip < -40) {
        direction = -direction;
    }

    glm::vec2 mousePos = glm::vec2(ofGetMouseX(),ofGetMouseY());
    for (int i=0; i<movers.size(); i++){
        
        glm::vec2 target    = mousePos - movers[i].pos;
        float distance      = glm::length(target);
        
        // repulse
        if (distance != 0 && distance < 100) {
            
            glm::vec2 direction = target / distance;
            movers[i].applyForce(-direction);
        }
        
        //attract
        else if (distance != 0 && distance < 200) {
            
            glm::vec2 direction = target / distance;
            movers[i].applyForce(direction);
        }
        
        movers[i].applyElasticForce(0.5);
        movers[i].applyDampingForce(0.2);
        movers[i].update();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    if (explain == false){
    ofSetColor(80);
    chakra11.drawString("Now, you can never escape till you buy it", 150,35);
    chakra11.drawString("Press ENTER to know more about the project.", 150,ofGetHeight()-50);
    
        ofPushMatrix();
        for (int i=0; i<movers.size(); i++)
        {
            movers[i].draw();
        }
        ofPopMatrix();
        
    ofSetColor(80);
    ofNoFill();
    ofDrawRectangle(targetX,targetY+100, 0,180,70);
    
    ofPushStyle();
    ofSetColor(80);
    chakra20.drawString("BUY NOW", targetX-40,targetY+110);
    ofPopStyle();
    
    
        
    ofPushMatrix();
        ofSetColor(219,85,75);
        ofFill();
        ofTranslate(targetX-63,targetY+100);
        ofRotateZ(ofGetElapsedTimef()*10);
        ofDrawRectangle(0,0,0,10,10);
        ofRotateDeg(45);
    ofPopMatrix();
    
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
    }
    
    
    if (explain){
        end.draw(ofGetWidth()*0.5,ofGetHeight()*.5,600,800);
        logo.draw(mouseX,mouseY,133,33);
        ofSetColor(255);
        chakra11.drawString("Press TAB to go back", 220,ofGetHeight()-50);
    }

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if (key == OF_KEY_RETURN){
        explain = true;
    }
    
    if (key == OF_KEY_TAB){
        explain = false;
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
