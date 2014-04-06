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
    Vec3 position;
    Vec3 velocity;
    Vec3 color;
    
    int name;
    
    Vec3 nextPosition;
    
    float mass;
    float volume;
    
    int3 boxID;
    int3 nextBoxID;
    
    void setPosition(float x, float y, float z);
    void changePosition(float x, float y, float z);
    void setVelocity(float x, float y, float z);
    void changeVelocity(float x, float y, float z);
    void setMass(float newMass);
    void setVolume(float newVolume);
    void setColor(float r, float g, float b);
    
    /*
     * Moves the particle forward based on 
     * it's current velocity.
     */
    void moveFromVelocity();
    
    Vec3 getVelocity();
	Vec3 getPosition();
    Vec3 getColor();
    
	float getMass();
	float getVolume();
};

#endif
