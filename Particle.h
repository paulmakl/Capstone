/*
 * Particle.cpp
 *
 *  Created on: Feb 3, 2014
 *  Author: Etan and Paul
 */

#pragma once
#ifndef PARTICLE_H_
#define PARTICLE_H_
#include "vectors.h"
#include <math.h>

class Particle
{
public:
    Vec2 position;
    Vec2 velocity;
    Vec3 color;
    
    Vec2 nextPosition;
    int2 nextBoxID;
    
    float mass;
    float volume;
    
    int2 boxID;
    
    
    void setPosition(float x, float y);
    void setVelocity(float x, float y);
    void setMass(float newMass);
    void setVolume(float newVolume);
    void setColor(float r, float g, float b);
    
    /*
     * Moves the particle forward based on 
     * it's current velocity.
     */
    void moveFromVelocity();
    
    Vec2 getVelocity();
	Vec2 getPosition();
    Vec3 getColor();
    
	float getMass();
	float getVolume();
};

#endif
