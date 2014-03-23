/*
 * Node.cpp
 *
 *  Created on: Feb 3, 2014
 *      Author: Etan
 */
#include "Node.h"

void Node::setForce(float x, float y, float z)
{
    force.x = x;
    force.y = y;
    force.z = z;
}

void Node::incForce(float x, float y, float z)
{
    force.x += x;
    force.y += y;
    force.z += z;
}

void Node::incParticlesNearNode(){
    particles_near_node++;
}

Vec3 Node::getForce()
{
    Vec3 ret;
    if(force.x == 0)
    	ret.x = 0.0f;
    else
    	ret.x = force.x/ particles_near_node;
    if(force.y == 0)
    	ret.y = 0.0f;
    else
    	ret.y = force.y/ particles_near_node;
    if(force.z ==0)
    	ret.z = 0.0f;
    else
    	ret.z = force.z/ particles_near_node;

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
    setForce(0.0f, 0.0f, 0.0f);
}

void Node::setForceColor(){
    float xforce = getForce().x;
    float yforce = getForce().y;
    float zforce = getForce().z;
    
    float approximate_maximum_speed = 0.3;
    
    float blue = fabs( xforce/approximate_maximum_speed ); //fabs function is Float Absolute value
    float red = fabs( yforce/approximate_maximum_speed );
    float green = fabs( zforce/approximate_maximum_speed );
    
    this -> setRGBA(red, green, blue, this -> color.a);
}
































