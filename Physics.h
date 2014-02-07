#ifndef PHYSICS_H_
#define PHYSICS_H_

#include "Environment.h"

class Physics{
public:
    Environment* env;
    
    //Physics(Environment* envPointer);
    void temp(Environment* envPointer);
    Vec2 interpolate(Vec2 a, Vec2 b, float offset);
    void updatePositions();
};

#endif