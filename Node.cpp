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

Vec2 Node::getForce(float x, float y)
	{
		return force;
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

