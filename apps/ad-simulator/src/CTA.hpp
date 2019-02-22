#pragma once

#include "ofMain.h"

class CTA {
public:
    
    void setup();
    void update();
    void draw();
  
    ofTrueTypeFont myfont;
    
    glm::vec2 pos;
    float r,g,b;
    int pick;
    float speed;
    
    
};
