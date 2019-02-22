#include "ofApp.h"

//--------------------------------------------------------------


void ofApp::setup(){
    ofBackground(220);
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofSetFrameRate(60);
//
//    ofSetLogLevel(OF_LOG_VERBOSE);
    
	leap.open();
    
    leap.setReceiveBackgroundFrames(true);
    
    cam.setOrientation(ofPoint(-20, 0, 0));
    
//    glEnable(GL_DEPTH_TEST);
//    glEnable(GL_NORMALIZE);
    
    chakra20.load("/Users/YinglanZHANG/Documents/of_v0.10.1_osx_release/apps/ADesirable/Scene4/bin/data/Chakra.ttf",20,true,true);
//    chakra12.load("/Users/YinglanZHANG/Documents/of_v0.10.1_osx_release/apps/ADesirable/Scene4/bin/data/Chakra.ttf",12,true,true);

    //set up bird
    rightTip = 0;
    lerping = 0.02;
    direction = 1;
   
    //
    yee = FALSE;
//    end.load("/Users/YinglanZHANG/Documents/of_v0.10.1_osx_release/apps/ADesirable/Scene4/bin/data/end.png");
    
    //movers
     ofSetCircleResolution(80);
    for (int y=0; y<10; y++) {
        for (int x=0; x<8; x++) {
            float posX = ofMap(x, 0, 7, -300, 300);
            float posY = ofMap(y, 0, 9, 400, -400);
            Mover mover( glm::vec2(posX, posY) );
            mover.mass = 5;
            movers.push_back(mover);
        }
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    simpleHands = leap.getSimpleHands();
    
    if( leap.isFrameNew() && simpleHands.size() ){
        
        leap.setMappingX(-230, 230, -ofGetWidth()/2, ofGetWidth()/2);
        leap.setMappingY(90, 490, -ofGetHeight()/2, ofGetHeight()/2);
        leap.setMappingZ(-150, 150, -200, 200);
        
        for(int i = 0; i < simpleHands.size(); i++){
            bool isLeft        = simpleHands[i].isLeft;
            handPos    = simpleHands[i].handPos;
          
         }
    }
	leap.markFrameAsOld();
    
    targetX = handPos.x+300;
    targetY = -handPos.y+300;
    x += (targetX - x);// * lerping;
    y += (targetY - y);// * lerping) - 0.5*direction;
    
    rightTip += 2*direction;
    
    if (rightTip > 120 || rightTip < -40) {
        direction = -direction;
    }

    glm::vec2 mousePos = glm::vec2(handPos.x,handPos.y);
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
    if(yee == false){
    ofSetColor(80);
    ofDrawBitmapString("Now, you can never escape till you buy it", 135,35);
        ofDrawBitmapString("click ENTER to know what's behind this project",120,ofGetHeight()-50);
    }
    
    cam.begin();
    ofPushMatrix();
    
        ofSetColor(80);
        ofNoFill();
        ofDrawRectangle(handPos.x,handPos.y, 0,180,70);
     chakra20.drawString("BUY NOW", handPos.x-40,handPos.y-10);
    
    ofPopMatrix();

    ofPushMatrix();
        for (int i=0; i<movers.size(); i++)
        {
            movers[i].draw();
        }
    ofPopMatrix();

    ofPushMatrix();
        ofSetColor(219,85,75);
        ofFill();
        ofTranslate(handPos.x-60,handPos.y);
        ofRotateZ(ofGetElapsedTimef()*10);
        ofDrawRectangle(0,0,0,10,10);
        ofRotateDeg(45);
    ofPopMatrix();
    
    cam.end();
    
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
    
    if (yee){
        ofSetColor(80);
        ofDrawBitmapString("Knowing that’s how advertisers track you down to cater you content  \nbased on your desire is scary, isn’t it? Luckily, such mind-targeted ads \nand inability to get out of the purchasing cycle aren’t the reality, yet. \n\nHowever, the reality isn’t much different. Here are some types of the\nreal consumer-targeting services media companies right now sell and \nprovide to advertisers: 'Geo-fencing', 'Geo-targeting', 'IP targeting', \n'Weather trigged delivery', '3rd-party data', 'Contextual & site \ntargeting', 'on-site retargeting', 'TV behavioral re-targeting'...\n Everything about you is being tracked and ads are directed \nto you through connected TV, digital videos, native advertising, your \nnetwork connections, clicks, browsing histories, audio files, social \nmedia,game consoles, mobile phones, and outdoor displays in real time, \nand inreal life. Meanwhile, the obsessive buying behavior has become a \nculture norm with the help of advancing technology. (exp: Buying through  \nclicking a button). The future form of the consumer journey will \nonly evolve more invisibly and intuitively, which will disguise the truth \nbehinnd the fabricated persuasion.",20,35);
        ofSetColor(219,85,75);
        ofDrawBitmapString("Know your data logging behaviors and digital trails. \nDon’t let ads follow your desires around. Be mindful.", 20,300);
    }
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if (key == OF_KEY_RETURN){
        yee = true;
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
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}

//--------------------------------------------------------------
void ofApp::exit(){
    // let's close down Leap and kill the controller
    leap.close();
}
