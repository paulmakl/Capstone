#ifndef PHYSICS_H_
#define PHYSICS_H_

#include "Environment.h"

class Physics{
<<<<<<< HEAD
public:
    Environment* env;
    
    //Physics(Environment* envPointer);
    void temp(Environment* envPointer);
    Vec2 interpolate(Vec2 a, Vec2 b, float offset);
    void updatePositions();
};

#endif
=======
    Environment* env;
    
    Physics(Environment* envPointer);
};

#endif
>>>>>>> 7c40d12ca73902e6aa832c090e28c900f5c17c32
