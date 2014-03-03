#ifndef PHYSICS_H_
#define PHYSICS_H_

#include "Environment.h"

#define force_gravity 0.01f;

class Physics
{
public:
    Environment* env;
    
    void init(Environment* envPointer);
    
    Vec2 interpolate(Vec2* a, Vec2* b, float offset);
    Vec2 extrapolate(Vec2 velocity, float offset);
    
    /*
     * This function requires that the environment's 
     * list of particles is sorted.
     */
    void updateGridForces();

    /*
     * Update the velocities of each particle
     * based on the grid forces in their surrounding
     * boxes.
     */
    void updateParticleVelocities();
    
    float calculateDistance(Vec2 a, Vec2 b);

    /*
     * Checks for collisions between
     * particles in the same box
     */
    void checkParticleCollisions();
    void checkParticlecollisionsAtIndex(int i, int2 boxID);
    
    /*
     * Based on the grid forces and each
     * particles inherent velocity,
     * update the positions of all particles
     */
    void updateParticlePositions();
    
    void addRandomVelocity();
    void gravity();

    void updateShapePositions();
    void checkEulerianCollisions();
    void resetNodes();
};

#endif
