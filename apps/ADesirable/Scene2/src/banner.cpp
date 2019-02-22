//
//  banner.cpp
//  Scene2
//
//  Created by Lan Z on 12/8/18.
//

#include "banner.hpp"

void banner::setup(){
    pos.x = ofRandom(-1000,1000);
    pos.y = ofRandom(-1000,1000);
    pos.z = ofRandom(-600,20);
    
    
    width = ofRandom(60,400);
    height = ofRandom(90,500);
    WH = glm::vec2(width,height);//size
    
    dotPos = glm::vec3 (pos.x,pos.y+0.25*WH.y,pos.z);
    dot.set(10);
    dot.setPosition(dotPos.x,dotPos.y,dotPos.z);
}

void banner::update() {
    //box
    dot.panDeg(0.7);
    dot.tiltDeg(0.7);
}


void banner::draw(){
    ofSetColor(80);
    ofNoFill();
    ofDrawRectangle(pos.x,pos.y,pos.z,WH.x,WH.y);
    ofFill();
    ofSetColor(220);
    ofDrawRectangle(pos.x+1,pos.y+1,pos.z,WH.x-2,WH.y-2);
    ofNoFill();
    ofSetColor(80);
    ofDrawRectangle(pos.x,pos.y-WH.y*.25,pos.z,WH.x*0.45,WH.y*0.1);
    ofSetColor(219,85,75);//red
    dot.drawWireframe(); //symbol
}
