#ifndef PHYSICS_H_
#define PHYSICS_H_

#include "Environment.h"

#define force_gravity 0.01f;

class Physics
{
public:
    Environment* env;
    
    void init(Environment* envPointer);
    
    Vec3 interpolate(Vec3* a, Vec3* b, float offset);
    Vec3 extrapolate(Vec3 velocity, float offset);
    
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
    
    Vec3 calculateDistance(Vec3 a, Vec3 b);

    /*
     * Checks for collisions between
     * particles in the same box
     */
    void checkParticleCollisions();
    void checkParticlecollisionsAtIndex(int i, int3 boxID);
    
    /*
     * Based on the grid forces and each
     * particles inherent velocity,
     * update the positions of all particles
     */
    void updateParticlePositions();
    
    void addRandomVelocity(int index);
    void gravity();

    void updateShapePositions();
    void checkEulerianCollisions();
    void resetNodes();
};

#endif
