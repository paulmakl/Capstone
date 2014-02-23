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
    void updateGridForces();
    void updateParticlePositions();
    void addRandomVelocity();
    void gravity();

    void updateShapePositions();
    void checkEulerianCollisions();
    void resetNodes();
};

#endif
