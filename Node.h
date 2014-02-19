/*
 * Node.h
 *
 *  Created on: Feb 3, 2014
 *      Author: Etan and Paul
 */

#include "vectors.h"
#include <cmath>
#pragma once
#ifndef NODE_H_
#define NODE_H_

/*
 * Nodes are the backbone of the Eularian Grid (in the Grid class).
 * E
 */

class Node
{
public:
	Vec4 color;
	Vec2 force;
    float particles_near_node;
    
    
    
	void setForce(float x, float y);
    void setRGBA(float r, float g, float b, float a);
    void setForceColor();

	Vec2 getForce();
	Vec4 getRGBA();
    
    void incParticlesNearNode();
    void incForce(float x, float y);
    
    void reset();
    
};

#endif