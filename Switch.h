#ifndef SWITCH_H_
#define SWITCH_H_

#ifdef __APPLE__
#define pixels 720
#else
#define pixels 900
#endif

#define xSize 64
#define ySize 64 // For now, keep xSize and ySize the same!
#define numParticles 100000
#define numShapes 1

#include "Physics.h"
#include "Draw.h"

class Switch{
public:
    Physics phys;
    Draw draw;
    Environment env;
    
    void init();
    void loop();
    
    
};

#endif