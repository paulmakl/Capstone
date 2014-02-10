/*
 * Cube.h
 *
 *  Created on: Feb 5, 2014
 *      Author: Etan
 */

#ifndef CUBE_H_
#define CUBE_H_

//#include "Node.h"
#include "vectors.h"
#include "Shape.h"
#pragma once

class Cube//: public Shape
{
public:
	Vec3 position;
	float length;

	void setVariables(float length, Vec3 position);
	void setPosition(Vec3 position);
	Vec3 getPosition();
	float getLength();
};

#endif /* CUBE_H_ */
