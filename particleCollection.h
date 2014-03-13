#ifndef PARTICLECOLLECTION_H_
#define PARTICLECOLLECTION_H_

#include "Particle.h"
#include "Configs.h"
#include "vectors.h"
#include <math.h>
#include <cstdlib>
#include <vector>
#include <iostream>

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
    /*
     * This 2d vector tracks the starting locations for each box
     * in the list of particles
     * boxes that have no particles in them have -1 as their index;
     */
    std::vector<std::vector<int> > indexTracker;

    int xSize;
    int numParticles;
    
    int carlSort(int value, int start);
    void shakerSort(int start, int end);
    int2 getParticlesListIndex(int2 boxID);
    
    int2 pseudoBinarySearch(int2 boxID);
    
    void initializeIndexTracker(int xSize, int ySize);
    private:
};


#endif
