/*
 * Shape.h
 *
 *  Created on: Feb 5, 2014
 *      Author: Etan
 */

#ifndef SHAPE_H_
#define SHAPE_H_

#include "Node.h"
#include "vectors.h"
#include "GLFuncs.h"
#pragma once

class Shape
{
public:
	Vec3 location;
	float size;

	void intersect(Node a);

	void draw();
};

#endif /* SHAPE_H_ */
