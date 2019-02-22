#pragma once
#include "ofMain.h"

class Plane : public ofNode {
public:
    
    Plane();
    
    void setup(float w, float h, float cols, float rows);
    void update();
    void draw();
    void drawWireframe();
    vector<glm::vec3> getVertices();
    
    ofMesh mesh;
    ofNode node;
    
    ofParameter<float> noiseAmp;
    ofParameter<float> noiseFreq;
    ofParameter<glm::vec2> noiseScale;
    ofParameter<ofColor> colorNear,colorFar;
    
};
