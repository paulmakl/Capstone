/*
 * Node.cpp
 *
 *  Created on: Feb 3, 2014
 *      Author: Etan
 */

class Node
{
public:
	Vec4 color;
	Vec2 force;

	void setForce(float x, float y)
	{
		force.x = x;
		force.y = y;
	}

	Vec2 getForce(float x, float y)
	{
		return force;
	}

	void setRGBA(float r, float g, float b, float a)
	{
		color.r = r;
		color.g = g;
		color.b = b;
		color.a = 1.0f;
	}

	Vec4 getRGBA()
	{
		return color;
	}
};
