/*
 * Particle.cpp
 *
 *  Created on: Feb 3, 2014
 *      Author: Etan and Paul
 */
#include "Particle.h"

void Particle::setPosition(float x, float y, float z)
{
	position.x = x;
	position.y = y;
	position.z = z;

	boxID.x = floor(position.x);
	boxID.y = floor(position.y);
	boxID.z = floor(position.z);

	nextBoxID.x = floor(position.x + velocity.x);
	nextBoxID.y = floor(position.y + velocity.y);
	nextBoxID.z = floor(position.z + velocity.z);
}

void Particle::setVelocity(float x, float y, float z)
{
	velocity.x = x;
	velocity.y = y;
	velocity.z = z;
}

void Particle::setMass(float newMass)
{
	mass = newMass;
}

void Particle:: setVolume(float newVolume)
{
	volume = newVolume;
}

void Particle::setColor(float r, float g, float b)
{
	color.x = r;
	color.y = g;
	color.z = b;
}

Vec3 Particle::getVelocity()
{
	return velocity;
}

Vec3 Particle::getPosition()
{
	return position;
}

Vec3 Particle::getColor()
{
	return color;
}

float Particle::getMass()
{
	return mass;
}

float Particle::getVolume()
{
	return volume;
}


void Particle::moveFromVelocity()
{
	position.x += velocity.x;
	position.y += velocity.y;
	position.z += velocity.z;

	boxID.x = floor(position.x);
	boxID.y = floor(position.y);
	boxID.z = floor(position.z);

	nextBoxID.x = floor(position.x + velocity.x);
	nextBoxID.y = floor(position.y + velocity.y);
	nextBoxID.z = floor(position.z + velocity.z);
}
