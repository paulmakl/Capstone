#ifndef PARTICLECOLLECTION_H_
#define PARTICLECOLLECTION_H_

#include "Particle.h"
#include "Configs.h"
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
    
private:
    int xSize;
    int numParticles;
    std::vector<Particle> particles;
    int carlSort(int value, int start);
    void shakerSort(int start, int end);
};


#endif
