/*
 * Cube.cpp
 *
 *  Created on: Feb 5, 2014
 *      Author: Etan
 */

#include "Cube.h"

void Cube::setVariables(float length2, Vec3 location2)
{
	length = length2;
	position = location2;
}

void Cube::setPosition(Vec3 location)
{
	position = location;
}

Vec3 Cube::getPosition()
{
	return position;
}

float Cube::getLength()
{
	return length;
}
