#ifndef PARTICLECOLLECTION_H_
#define PARTICLECOLLECTION_H_

#include "Particle.h"
#include "Configs.h"
#include "vectors.h"
#include <math.h>
#include <cstdlib>
#include <vector>

//using std::vector;

class ParticleCollection{
public:
    
    /*
     * different initialization methods
     */
    void init(float nparticles, int xSize, int ySize);
    void init2(float nparticles, int xSize, int ySize);
    void sortParticles();
    Particle* getParticle(int index);
    std::vector<Particle> particles;

    int xSize;
    int numParticles;
    
    int carlSort(int value, int start);
    void shakerSort(int start, int end);
    int2 getParticlesListIndex(int2 boxID);
    private:
};


#endif
