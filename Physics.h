#ifndef PHYSICS_H_
#define PHYSICS_H_

#include "Environment.h"

class Physics{
public:
    Environment* env;
    
    void init(Environment* envPointer);
    
    Vec2 interpolate(Vec2* a, Vec2* b, float offset);
    Vec2 fullInterpolate(Vec2* a, Vec2* b, Vec2* p);
    Vec2 extrapolate(Vec2 velocity, float offset);
    void updateGridForces();
    void updateParticlePositions();
    void addRandomVelocity();

    void updateShapePositions();
    void checkEulerianCollisions();
    void resetNodes();
    
    float bilinearInterpolation(float q11, float q21, float q12, float q22);
};

#endif
