/*
 * Sphere.h
 *
 *  Created on: Feb 5, 2014
 *      Author: Etan
 */

#ifndef SPHERE_H_
#define SPHERE_H_

//#include "Node.h"
//#include "vectors.h"
//#include "GLFuncs.h"
#include "Shape.h"
#pragma once

class Sphere: public Shape
{
public:
	Vec3 location;
	float radius;

	void intersect(Node a);
	void draw();
};
#endif /* SPHERE_H_ */
