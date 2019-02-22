#include "ofApp.h"

static int pts[] = {100,100,200,200,300,50};
static int nPts  = 3*2;

//--------------------------------------------------------------
void ofApp::setup() {
    ofSetVerticalSync(true);
    ofBackgroundHex(0xfdefc2);
    ofSetLogLevel(OF_LOG_NOTICE);
    
    bMouseForce = false;
    
    box2d.init();
    box2d.setGravity(0, 10);
    box2d.createGround();
    box2d.setFPS(60.0);
    box2d.registerGrabbing();
    
    // lets add a contour to start
    for(int i=0; i<nPts; i+=2) {
        float x = pts[i];
        float y = pts[i+1];
        edgeLine.addVertex(x, y);
    }
    
    // make the shape
    edgeLine.setPhysics(0.0, 0.5, 0.5);
    edgeLine.create(box2d.getWorld());
}

//--------------------------------------------------------------
void ofApp::update() {
    
    box2d.update();
    
    if(bMouseForce) {
        float strength = 8.0f;
        float damping  = 0.7f;
        float minDis   = 100;
        for(int i=0; i<circles.size(); i++) {
            circles[i].get()->addAttractionPoint(mouseX, mouseY, strength);
            circles[i].get()->setDamping(damping, damping);
        }
        for(int i=0; i<customParticles.size(); i++) {
            customParticles[i].get()->addAttractionPoint(mouseX, mouseY, strength);
            customParticles[i].get()->setDamping(damping, damping);
        }
    }
    
    // remove shapes offscreen
    ofRemove(boxes, ofxBox2dBaseShape::shouldRemoveOffScreen);
    ofRemove(circles, ofxBox2dBaseShape::shouldRemoveOffScreen);
    ofRemove(customParticles, ofxBox2dBaseShape::shouldRemoveOffScreen);
}


//--------------------------------------------------------------
void ofApp::draw() {
    
    for(int i=0; i<circles.size(); i++) {
        ofFill();
        ofSetHexColor(0x90d4e3);
        circles[i].get()->draw();
    }
    
    for(int i=0; i<boxes.size(); i++) {
        ofFill();
        ofSetHexColor(0xe63b8b);
        boxes[i].get()->draw();
    }
    
    for(int i=0; i<customParticles.size(); i++) {
        customParticles[i].get()->draw();
    }
    
    ofNoFill();
    ofSetHexColor(0x444342);
    if(drawing.size()==0) {
        edgeLine.updateShape();
        edgeLine.draw();
    }
    else drawing.draw();
    
    string info = "";
    info += "Press [s] to draw a line strip ["+ofToString(bDrawLines)+"]\n";
    info += "Press [f] to toggle Mouse Force ["+ofToString(bMouseForce)+"]\n";
    info += "Press [c] for circles\n";
    info += "Press [b] for blocks\n";
    info += "Press [z] for custom particle\n";
    info += "Total Bodies: "+ofToString(box2d.getBodyCount())+"\n";
    info += "Total Joints: "+ofToString(box2d.getJointCount())+"\n\n";
    info += "FPS: "+ofToString(ofGetFrameRate())+"\n";
    ofSetHexColor(0x444342);
    ofDrawBitmapString(info, 30, 30);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    
    if(key == 'c') {
        float r = ofRandom(4, 20);        // a random radius 4px - 20px
        circles.push_back(shared_ptr<ofxBox2dCircle>(new ofxBox2dCircle));
        circles.back().get()->setPhysics(3.0, 0.53, 0.1);
        circles.back().get()->setup(box2d.getWorld(), mouseX, mouseY, r);
        
    }
    
    if(key == 'b') {
        float w = ofRandom(4, 20);
        float h = ofRandom(4, 20);
        boxes.push_back(shared_ptr<ofxBox2dRect>(new ofxBox2dRect));
        boxes.back().get()->setPhysics(3.0, 0.53, 0.1);
        boxes.back().get()->setup(box2d.getWorld(), mouseX, mouseY, w, h);
    }
    
    if(key == 'z') {
        
        customParticles.push_back(shared_ptr<CustomParticle>(new CustomParticle));
        CustomParticle * p = customParticles.back().get();
        float r = ofRandom(3, 10);        // a random radius 4px - 20px
        p->setPhysics(0.4, 0.53, 0.31);
        p->setup(box2d.getWorld(), mouseX, mouseY, r);
        p->color.r = ofRandom(20, 100);
        p->color.g = 0;
        p->color.b = ofRandom(150, 255);
    }
    
    if(key == 'f') bMouseForce = !bMouseForce;
    if(key == 't') ofToggleFullscreen();
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
    drawing.addVertex(x, y);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
    
    if(edgeLine.isBody()) {
        drawing.clear();
        edgeLine.destroy();
    }
    
    drawing.addVertex(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
    
    drawing.setClosed(false);
    drawing.simplify();
    
    edgeLine.addVertexes(drawing);
    //polyLine.simplifyToMaxVerts(); // this is based on the max box2d verts
    edgeLine.setPhysics(0.0, 0.5, 0.5);
    edgeLine.create(box2d.getWorld());
    
    drawing.clear();
}

//--------------------------------------------------------------
void ofApp::resized(int w, int h){
    
}
