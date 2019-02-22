#include "Mover.hpp"


Mover::Mover()
{
    
    origPos = glm::vec2(0,0);
    pos = glm::vec2(0,0);
    vel = glm::vec2(0,0);
    acc = glm::vec2(0,0);
    
    mass = 5;
}

Mover::Mover(glm::vec2 _pos)
{
    
    origPos = _pos;
    pos = origPos;
    vel = glm::vec2(0,0);
    acc = glm::vec2(0,0);
    
    mass = 5;
}

void Mover::applyForce(glm::vec2 force)
{
    acc += force / mass;
}

void Mover::applyDampingForce(float strength)
{
    float speed = glm::length(vel);
    if (speed != 0){
        glm::vec2 dir = vel / speed;
        applyForce( -dir * strength );
    }
}

void Mover::applyElasticForce(float strength)
{
    glm::vec2 diff = origPos - pos;
    float length = glm::length(diff);
    if (length != 0){
        glm::vec2 dir = diff / length;
        elasticForce = dir * strength;
        applyForce( elasticForce );
    
    }
    
    
}

void Mover::update()
{
    vel += acc;
    pos += vel;
    acc *= 0;
}

void Mover::draw()
{
    ofPushStyle();
    ofFill();
    ofSetColor(219,85,75,60);
    
    ofDrawRectangle(pos.x,pos.y, mass * 2.0 ,mass * 2.0);      // base radius on mass
    
    ofPopStyle();
}
