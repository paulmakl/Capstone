/*
 * Particle.cpp
 *
 *  Created on: Feb 3, 2014
 *      Author: Etan and Paul
 */
#include "vectors.h"
#pragma once
#ifndef PARTICLE_H_
#define PARTICLE_H_

class Particle
{
public:
    Vec2 position;
    Vec2 velocity;
    float mass;
    
    void setPosition(float x, float y);
    void setVelocity(float x, float y);
    void setMass(float newMass);
    
    Vec2 getVelocity();
	Vec2 getPosition();
	float getMass();
};

#endif
