/*
 * Particle.cpp
 *
 *  Created on: Feb 3, 2014
 *      Author: Etan and Paul
 */
#include "Particle.h"

void Particle::setPosition(float x, float y)
{
    position.x = x;
    position.y = y;
    boxID.x = floor(position.x);
    boxID.y = floor(position.y);
}

void Particle::setVelocity(float x, float y)
{
    velocity.x = x;
    velocity.y = y;
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

Vec2 Particle::getVelocity()
{
    return velocity;
}

Vec2 Particle::getPosition()
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
    boxID.x = floor(position.x);
    boxID.y = floor(position.y);
}
