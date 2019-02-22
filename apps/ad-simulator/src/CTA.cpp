#include "CTA.hpp"

void CTA::setup(){
//    pos = glm::vec2(ofRandom(0,ofGetWidth()-150),ofRandom(0,ofGetHeight()-80));
//    pos = glm::vec2(ofRandom(550,1700),ofRandom(550,950));//Big SCREEN
     pos = glm::vec2(ofRandom(900,1200),ofRandom(560,900));//SMALL SCREEN
//     ofDrawRectangle(550,550,1200,480);//middle bottom
    r = ofRandom(0,255);
    g = ofRandom(0,255);
    b = ofRandom(0,255);
    myfont.load("Chakra.ttf", 20);
    
    pick = int(ofRandom(0,5));
}

void CTA::update(){
    
    speed = ofRandom(-.1,.1);
    pos.x += speed;
    pos.y += speed;
    
    
}

void CTA::draw(){
    
    if(pick == 0){
        ofPushStyle();
        ofFill();
        ofSetColor(0,60);
        ofDrawRectangle(pos,150,80);
        //    ofNoFill();
        ofSetColor(r,g,b,80);
        //    ofSetLineWidth(5);
        ofDrawRectangle(pos.x+5,pos.y+5,140,70);
        ofPopStyle();
        
        ofSetColor(255);
        myfont.drawString("BUY NOW",pos.x+15,pos.y+50);// \n is next line
    } else if (pick == 1){
        ofPushStyle();
        ofFill();
        ofSetColor(0,60);
        ofDrawRectangle(pos,170,80);
        //    ofNoFill();
        ofSetColor(r,g,b,80);
        //    ofSetLineWidth(5);
        ofDrawRectangle(pos.x+5,pos.y+5,160,70);
        ofPopStyle();
        ofSetColor(255);
        myfont.drawString("Learn More",pos.x+15,pos.y+50);
        
    } else if (pick == 2){
        ofPushStyle();
        ofFill();
        ofSetColor(0,60);
        ofDrawRectangle(pos,190,80);
        //    ofNoFill();
        ofSetColor(r,g,b,80);
        //    ofSetLineWidth(5);
        ofDrawRectangle(pos.x+5,pos.y+5,180,70);
        ofPopStyle();
        ofSetColor(255);
        myfont.drawString("Get it Today!",pos.x+15,pos.y+50);
    } else if (pick == 3){
        ofPushStyle();
        ofSetColor(0,60);
        ofDrawRectangle(pos,150,80);
        //    ofNoFill();
        ofSetColor(r,g,b,80);
        //    ofSetLineWidth(5);
        ofDrawRectangle(pos.x+5,pos.y+5,140,70);
        ofPopStyle();
        ofSetColor(255);
        myfont.drawString("Shop Now",pos.x+15,pos.y+50);
    } else if (pick == 4){
        ofPushStyle();
        ofFill();
        ofSetColor(0,60);
        ofDrawRectangle(pos,165,80);

        ofSetColor(r,g,b,80);
        ofDrawRectangle(pos.x+5,pos.y+5,155,70);
        ofPopStyle();
        ofSetColor(255);
        myfont.drawString("Don't wait!",pos.x+15,pos.y+50);
    }
}
