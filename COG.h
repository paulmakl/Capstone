#ifndef COG_H_
#define COG_H_
#include <vector>
#include "particle.h"
#include "vectors.h"
using namespace std;

class COG{
public:
    vector <Particle*> particles;
    Vec3 center;
    int numParticles;
    
    void updateCenter();
    void addParticles(Particle* p);
};

#endif