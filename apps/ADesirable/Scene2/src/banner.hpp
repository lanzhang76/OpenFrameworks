#pragma once

#include "ofMain.h"

class banner {
public:
    
    void setup();
    void update();
    void draw();
    
    glm::vec3 pos, dotPos;
    glm::vec2 WH;
    
    ofPlanePrimitive banner, bannerBorder;
    
    float width, height;
    
    ofBoxPrimitive dot;
    
};


