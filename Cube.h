/*
 * Cube.h
 *
 *  Created on: Feb 5, 2014
 *      Author: Etan
 */

#ifndef CUBE_H_
#define CUBE_H_

//#include "Node.h"
//#include "vectors.h"
#include "Shape.h"
#pragma once

class Cube: public Shape
{
public:
	Vec3 location;
	float length;

	void intersect(Node a);
	void draw();
	void setVariables(float length2, Vec3 location2);
};

#endif /* CUBE_H_ */
