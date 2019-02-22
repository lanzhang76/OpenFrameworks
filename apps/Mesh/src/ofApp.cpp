#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    
    gui.setup();
      //set("name",default value, minumum, max)
    gui.add(scale.set("scale",100.0,0.0,1000.0));
    gui.add(pos.set("position",glm::vec3(0),glm::vec3(-500),glm::vec3(500)));
    gui.add(mode.set("mode",0.0,0.0,2.0));
    gui.add(mesh.noiseScale.set("Scale",glm::vec2(0.2),glm::vec2(0.),glm::vec2(.4)));
    gui.add(mesh.noiseFreq.set("Frequency",1.,0.,10));
    gui.add(mesh.noiseAmp.set("Amplitude",1.,0.,100));
    gui.add(mesh.colorNear.set("color near", ofColor::fuchsia,ofColor(0,0,0),ofColor(255,255,255)));
    gui.add(mesh.colorFar.set("color far", ofColor::navy,ofColor(0,0,0),ofColor(255,255,255)));
    
//    ofMesh& mesh = box.getMesh();//not duplicate, but accept the mesh in shape
//    mesh.addVertex(glm::vec3(300,300,300));
//
//    float meshWidth = 500;
//    float meshHeight = 500;
//
//    int rows = 100;
//    int cols = 100;
//
    mesh.setup(500,500,100,100);
    
    
}

//--------------------------------------------------------------
void ofApp::update(){
  
    mesh.update();
    mesh.setPosition(pos);
    mesh.setScale(scale);
    
    
//    box.setPosition(pos);//ofNode Primitive
//    box.set(size);//ofBox Position
//
//    vector<glm::vec3>& vertices = mesh.getVertices();
//    float time = ofGetElapsedTimef();
//
//    for (int i = 0; i < vertices.size(); i++){
//        vertices[i].x += ofSignedNoise(vertices[i] + glm::vec3(time * noiseFreq)) * noiseAmp;
//        vertices[i].y += ofSignedNoise(vertices[i] + glm::vec3((time+100) * noiseFreq)) * noiseAmp;
//        vertices[i].z += ofSignedNoise(vertices[i] + glm::vec3((time+200) * noiseFreq)) * noiseAmp;
//    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    cam.begin();
    ofEnableDepthTest();
    
//    ofDrawAxis(300);
    
    if(mode == 0){
        mesh.draw();
    }
    else if (mode == 1){
        mesh.drawWireframe();
    } else if (mode == 2){
//        box.drawVertices();
//        for (int i = 0; i<box.getMesh().getVertices().size(); i ++){
//            ofDrawSphere(box.getMesh().getVertices()[i],3);
//        }
        for (int i = 0; i<mesh.getVertices().size(); i ++){
            ofDrawSphere(mesh.getVertices()[i],3);
        }
        
    }
    
    
    ofDisableDepthTest();
    cam.end();
    gui.draw();
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
