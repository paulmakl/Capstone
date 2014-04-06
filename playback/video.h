#ifndef VIDEO_H_
#define VIDEO_H_
#include "vectors.h"
#include "state.h"

class video{
public:
    int3 size;
    Vec3 cameraPos;
    int numParticles;
    std::vector<state> states;
    
    void addState();
};

#endif