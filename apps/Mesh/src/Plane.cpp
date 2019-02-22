//
//  Plane.cpp
//  Week11_mesh
//
//  Created by Lan Z on 11/6/18.
//

#include "Plane.hpp"


Plane::Plane(){
    
}

void Plane::setup(float w, float h, float cols, float rows){
    
//    
//    float meshWidth = 500;
//    float meshHeight = 500;
//    
//    int rows = 100;
//    int cols = 100;
    
    
    for (int r = 0; r < rows; r++){
        for(int c = 0; c <cols; c++){
            glm::vec3 p;
            p.x = ofMap(r,0,rows-1,w * -.5, w *.5);
            p.y = ofMap(c,0,cols-1,h * .5, h * -.5);
            p.z = 0;
            mesh.addVertex(p);
            mesh.addColor(ofColor());
            
            //1 grid square = 2 triangles
            //
            // A------B ----
            // |    / |
            // |   /  |
            // |  /   |
            // D ---- C ----
            // |      |
            // |      |
            
            if (c < cols-1 && r <rows-1){
                int index = r * cols +c;
                
                //traingle 1
                mesh.addIndex(index); //A
                mesh.addIndex(index + 1); //B
                mesh.addIndex(index + cols);//D
                
                //traingle 2
                mesh.addIndex(index + 1);//B
                mesh.addIndex(index + 1 + cols);//C
                mesh.addIndex(index + cols);//D
            }
        }
    }
    
}

void Plane::update(){
    
    float time = ofGetElapsedTimef();
    
    for (int i = 0; i < mesh.getVertices().size(); i++){
        glm::vec3& vertex = mesh.getVertices()[i];
        float noise = ofSignedNoise(vertex.x*noiseScale.get().x,vertex.y*noiseScale.get().y,time*noiseFreq);
        vertex.z = noise * noiseAmp;
        
        float depthPercent = ofMap(vertex.z,-noiseAmp,noiseAmp,0,1);
        
        ofColor color = colorFar.get().getLerped(colorNear.get(),depthPercent);
        
        mesh.getColors()[i] = color;
        
        
    }
    
    
}

void Plane::draw(){
    
    ofPushMatrix();
    
//    ofTranslate(getPosition());
//    ofScale(getScale());
    ofMultMatrix(node.getGlobalTransformMatrix());
    
    mesh.draw();
    
    ofPopMatrix();
}

void Plane::drawWireframe(){
      mesh.drawWireframe();
}

vector<glm::vec3> Plane::getVertices(){
    return  mesh.getVertices();
}
