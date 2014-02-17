/*
 * Node.h
 *
 *  Created on: Feb 3, 2014
 *      Author: Etan and Paul
 */

#include "vectors.h"
#pragma once
#ifndef NODE_H_
#define NODE_H_

class Node
{
public:
	Vec4 color;
	Vec2 force;
    float particles_near_node;
    
	void setForce(float x, float y);
    void incForce(float x, float y);
    
	Vec2 getForce();
    
	void setRGBA(float r, float g, float b, float a);
    
	Vec4 getRGBA();
    
    void reset();
    
    void incParticlesNearNode();
};

#endif