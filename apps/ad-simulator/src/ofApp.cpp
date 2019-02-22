#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
//    ofBackground(54, 54, 54);
    ofBackground(225,160,182);
    
    ofSetFrameRate(60);
    
    //OSC setup
    const int RECEIVE_PORT   = 7000;
    receiver.setup(RECEIVE_PORT);
    
    //web cam set up
    int camWidth         = 500;
    int camHeight         = 370;
    cam.setup(camWidth,camHeight);
    
    finder.setup("haarcascade_frontalface_default.xml");
    finder.setPreset(ObjectFinder::Preset::Fast);
    finder.getTracker().setPersistence(30);
    
    //image objects
    ketchup.load("Ketchup.png");
    lip.load("Lip.png");
    
    //text set up
    Chakra60.load("Chakra.ttf",50,true,true);
    verdana30.setLineHeight(50.0f);
    verdana30.setLetterSpacing(5);
    //
    verdana30.load("verdana.ttf", 18, true, true);
    verdana30.setLineHeight(34.0f);
    verdana30.setLetterSpacing(1.035);
    //
    verdana14.load("verdana.ttf", 14, true, true);
    verdana14.setLineHeight(18.0f);
    verdana14.setLetterSpacing(1.037);
    //
    
    bFirst  = true;
    typeStr = " ";

    randomizeViewports();
    
    //banners
    for (int i = 0; i < banners.size(); i++){
        banners[i].setup();
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    //OSC message coming in
    ofxOscMessage m;
    while(receiver.hasWaitingMessages()){
        receiver.getNextMessage(m);
//        string address = m.getAddress();
//                cout << "    address: " << address;
        //alpha
        if (m.getAddress() == "Muse-2C07/elements/alpha_relative"){
//        cout << "getting alpha" <<endl;
            alpha = m.getArgAsFloat(1);
            alphaTrans = ofMap(alpha, 0,0.4,1,100);
            if (alphaTrans != alphaStorage[(index - 1 + store)/store]){
                alphaStorage[index] = alphaTrans;
                index = (index + 1) % store;
            }
            alphaMean = (alphaStorage[0]+alphaStorage[1]+alphaStorage[2]+alphaStorage[3]+alphaStorage[4])*0.2;
        }
        }
        
        //acc
        if (m.getAddress() == "Muse-2C07/acc"){
            acc.x = m.getArgAsFloat(0);
            acc.y = m.getArgAsFloat(1);
            acc.z = m.getArgAsFloat(2);
//             cout << acc <<endl;
        }
    
        //blink
        if (m.getAddress() == "Muse-2C07/elements/blink"){
            cout << blink <<endl;
            blink = m.getArgAsBool(0);
//            if (blink == 1){ blinkVal = "yes";}
//            else if (blink == 0) {blinkVal = "no";}
        }
    
    //banners
    for(int i = 0; i < banners.size(); i ++){
        banners[i].update();
    }
    
    
    //web cam
    cam.update();
    if (cam.isFrameNew()){
        finder.update(cam);
    }
    
    
    
}


//--------------------------------------------------------------
void ofApp::draw(){
    
    //    web cam draw
    cam.draw(21,661);
    
    
    //alpha num
    ofSetColor(255);
     for (int k = 0; k < store; k++) {
    ofDrawBitmapString("alpha: " + ofToString(alphaStorage[k]), ofGetWidth()-200, 120+20*k);
//    ofDrawBitmapString("blink: " + blinkVal, ofGetWidth()-200, 220);
         ofDrawBitmapString("blink: " +ofToString(blink), ofGetWidth()-200, 220);
    ofDrawBitmapString("alphaMean: " + ofToString(alphaMean), ofGetWidth()-200, 240);
}
    
    
    //signal checking
    ofSetColor(230,20,240);
    ofDrawCircle(ofGetWidth()-60,60,20,20);
    verdana14.drawString("sig-status",ofGetWidth()-120,90);
    
    
    
    //header
    ofPopStyle();
    ofSetColor(115,230,255);
    Chakra60.drawString("ADesirable",60,85);
    ofNoFill();
    ofSetLineWidth(1);
    ofDrawRectangle(20,20,400,90);
    ofDrawRectangle(24,24,392,82);
    ofPushStyle();
    //
    ofSetColor(245, 58, 135);
    verdana14.drawString("Today is: Oct 30th 2041 | Weather: Sunny", 20, 140);
    verdana14.drawString("We hope you have a wonderful day.", 20, 170);
    
    //
    ofSetColor(255);
    verdana30.drawString("Dear "+ typeStr + ", you will like these today:", 20, 205);
    
    //
    ofSetColor(245, 58, 135);
    verdana14.drawString("Hey! "+ typeStr + ", your friend loved our burger:", 580, 480);
   
    
    //draw 3d scence
    ofPushMatrix();
    ofPushStyle();
    drawViewportOutline(viewport3D);
    camera.begin(viewport3D);
   
    rotation.x = ofMap(acc.x,-1,1,0,100);
    rotation.y = ofMap(acc.y,-1,1,0,100);
    rotation.z = ofMap(acc.z,-1,1,0,100);
    ofDrawSphere(rotation.x,rotation.y,100);
    ofRotateXDeg(rotation.x);
    ofRotateYDeg(rotation.y);
    ofRotateZDeg(rotation.z);
    ofDrawGrid(100);
    camera.end();
    ofPopStyle();
    ofPopMatrix();
    
    //frames
    ofPushStyle();
    ofSetColor(115,230,255);
    ofNoFill();
    ofSetLineWidth(1);
    ofDrawRectangle(20,240,500,370);//Left Top
    ofDrawRectangle(20,660,500,370);//left Bottom
//    ofDrawRectangle(550,20,800,480);//middle top
//    ofDrawRectangle(550,550,1200,480);//middle bottom
    ofDrawRectangle(550,20,800,480);//middle top(small screen)
    ofDrawRectangle(550,550,1000,320);//middle bottom
    ofFill();
    ofPopStyle();
    
    //burger
    ofPushStyle();
    ofSetColor(230,200,230);
    ofNoFill();
    ketchup.draw(800,250,alphaMean*1.5,alphaMean*3);
//    ofDrawCircle(800,250,alphaMean*1.5,alphaMean*1.5);
    ofPopStyle();
    
    //lips
    ofPushStyle();
    ofSetColor(ofMap(alphaTrans,0,100,100,255),alphaTrans*0.5,0);
    ofFill();//change the lips to neutral
    lip.draw(600,650,300,150);
//    ofDrawRectangle(600,650,200,100);
    ofDrawBitmapString("We pick this color just for you:", 600,620);
    ofPopStyle();
    
//    banners
    int MaxNum = 1;
    if(blink == 1){
    for(int i = 0; i < MaxNum; i ++){
        CTA banner;
        banner.setup();
        banners.push_back(banner);
        }}
    for (int b = 0; b < banners.size(); b++){
            banners[b].draw();
        }
    if (blink == 0){
        for(int i = 0; i < banners.size(); i ++){
            banners.clear();
        }
    }

//    pop name
//    ofPushMatrix();
//    ofRectangle bounds = verdana14.getStringBoundingBox(typeStr, 0, 0);
//    ofTranslate(30 + bounds.width/2, 380 + bounds.height / 2, 0);  //pos
//    ofScale(2.0 + sin(ofGetElapsedTimef()), 2.0 + sin(ofGetElapsedTimef()), 1.0);//scale level
//    ofSetColor(205);
//    verdana14.drawString(typeStr+", get them today!", -bounds.width/2+400, bounds.height/2 );//what to display
//    ofPopMatrix();

    ofDrawBitmapStringHighlight(ofToString(ofGetFrameRate()), 20, 20);

}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
//    inputCharacter = key;
    if(key == OF_KEY_DEL || key == OF_KEY_BACKSPACE){
        typeStr = typeStr.substr(0, typeStr.length()-1);
    }
    else if(key == OF_KEY_RETURN ){
        typeStr += "\n";
    }else{
        if( bFirst ){
            typeStr.clear();
            bFirst = false;
        }
        ofUTF8Append(typeStr,key);
    }

}

//--------------------------------------------------------------
void ofApp::randomize(ofRectangle & viewport){
//    viewport.x = ofRandom(ofGetWidth() * 2.0f / 3.0f);
//    viewport.y = ofRandom(ofGetHeight() * 2.0f / 3.0f);
//    viewport.width = 100 + ofRandom(ofGetWidth() - viewport.x - 100);
//    viewport.height = 100 + ofRandom(ofGetHeight() - viewport.y - 100);
    viewport.x = 20;
    viewport.y = 240;
    viewport.width = 500;
    viewport.height = 370;
}

//--------------------------------------------------------------
void ofApp::randomizeViewports(){
    randomize(viewport3D);
}

//--------------------------------------------------------------
void ofApp::drawViewportOutline(const ofRectangle & viewport){
//    ofPushStyle();
//    ofFill();
//    ofSetColor(50);
//    ofSetLineWidth(0);
//    ofDrawRectangle(viewport);
    ofNoFill();
    ofSetColor(25);
    ofSetLineWidth(1.0f);
    ofDrawRectangle(viewport);
    ofPopStyle();
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    for(int i = 0; i < banners.size(); i ++){
        banners.clear();
    }
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
