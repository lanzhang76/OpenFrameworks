#include "ofApp.h"

static int pts[] = {100,450,150,650,450,650,500,450};
static int nPts  = 4*2;


//--------------------------------------------------------------
void ofApp::setup() {
    chakra11.load("Chakra.ttf",11, true,true);
    cartImage.load("cart.png");
    
    
    const int RECEIVE_PORT   = 7000;
    receiver.setup(RECEIVE_PORT);
    
    ofSetVerticalSync(true);
    ofBackground(220);
    ofSetFrameRate(60);
    ofSetLogLevel(OF_LOG_NOTICE);
    
    box2d.init();
    box2d.setGravity(0, 1.5);
    box2d.createBounds();
    box2d.setFPS(30.0);
    box2d.registerGrabbing();
    
    cart = false;
    transition = false;
    blinked = false;
    
    //basket
    for(int i=0; i<nPts; i+=2) {
        float x = pts[i];
        float y = pts[i+1];
        edgeLine.addVertex(x, y);
    }
    edgeLine.setPhysics(0.0, 0.5, 0.5);
    edgeLine.create(box2d.getWorld());
    
}

//--------------------------------------------------------------
void ofApp::update() {
    box2d.update();
    
    ofxOscMessage m;
    while(receiver.hasWaitingMessages()){
//        cout << "received" <<endl;
 receiver.getNextMessage(m);
        if (m.getAddress() == "Muse-2C07/elements/blink"){
            cout << blink <<endl;
            blink = m.getArgAsBool(0);
            if (blink == 1){
                blinked = true;
            }else if (blink == 0) {
                blinked = false;
            }
        }
    }
    
    if(blinked) {
//        float time = ofGetElapsedTimef();
//        if (time >5000){
        float w = 15;
        float h = 15;
        boxes.push_back(shared_ptr<ofxBox2dRect>(new ofxBox2dRect));
        boxes.back().get()->setPhysics(1.0, 0.3, 0.1);
        boxes.back().get()->setup(box2d.getWorld(), ofRandom(100,500), 1, w, h);
        cart = true;
//        }
    }
}

//--------------------------------------------------------------
void ofApp::draw() {
    
    edgeLine.draw();
    
    
    for(int i=0; i<boxes.size(); i++) {
        ofNoFill();
        ofSetColor(220,85,75);
        boxes[i].get()->draw();
    }
    
    // draw the ground
    box2d.drawGround();
    
    string info = "";
//    info += "Press [b] for blocks\n";
    info += "Total: $"+ofToString(-40+20*box2d.getBodyCount())+"\n";
    ofSetColor(80);
    chakra11.drawString(info, 260, ofGetHeight()-110);
    chakra11.drawString("Adding items to your shopping cart has never been easier.", 110, 35);
    chakra11.drawString("(Just blink)", 260, 55);
    chakra11.drawString(ofToString(blinked), 260, 80);
    
    if(cart == true){
    ofSetColor(80);
    chakra11.drawString("Added to the cart!", 230, ofGetHeight()*0.5);
       
        if (ofGetFrameNum() % 100 == 0){
            cart = false;
        }
    }
   
    cartImage.draw(0,0,600,800);
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    if (key == 'b'){
        float w = 15;
        float h = 15;
        boxes.push_back(shared_ptr<ofxBox2dRect>(new ofxBox2dRect));
        boxes.back().get()->setPhysics(1.0, 0.3, 0.1);
        boxes.back().get()->setup(box2d.getWorld(), ofRandom(100,500), 1, w, h);
        cart = true;
    }
    
   
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
    
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
    
}

//--------------------------------------------------------------
void ofApp::resized(int w, int h){
    
}
