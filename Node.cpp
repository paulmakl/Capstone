/*
 * Node.cpp
 *
 *  Created on: Feb 3, 2014
 *      Author: Etan
 */
#include "Node.h"

void Node::setForce(float x, float y)
{
    force.x = x;
    force.y = y;
}

void Node::incForce(float x, float y)
{
    force.x += x;
    force.y += y;
}

void Node::incParticlesNearNode(){
    particles_near_node++;
}

Vec2 Node::getForce()
{
    Vec2 ret;
    if(force.x == 0)
    	ret.x = 0.0f;
    else
    	ret.x = force.x/ particles_near_node;
    if(force.y == 0)
    	ret.y = 0.0f;
    else
    	ret.y = force.y/ particles_near_node;

    return ret;
}

void Node::setRGBA(float r, float g, float b, float a)
{
    color.r = r;
    color.g = g;
    color.b = b;
    color.a = 1.0f;
}

Vec4 Node::getRGBA()
{
    return color;
}

void Node::reset()
{
    particles_near_node = 0;
    setForce(0.0f, 0.0f);
}

void Node::setForceColor(){
    float xforce = getForce().x;
    float yforce = getForce().y;
    
    float approximate_maximum_speed = 0.01;
    
    float blue = fabs( xforce/approximate_maximum_speed ); //fabs function is Float Absolute value
    float red = fabs( yforce/approximate_maximum_speed );
    
    this -> setRGBA(blue, this -> color.g, red, this -> color.a);
}
































