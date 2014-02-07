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
}
void Particle::setVelocity(float x, float y)
{
    velocity.x = x;
    velocity.y = y;
}
Vec2 Particle::getVelocity()
{
    return velocity;
}
Vec2 Particle::getPosition()
{
    return position;
}