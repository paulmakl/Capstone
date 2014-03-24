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

class ParticleCollection
{
public:

	/*
	 * different initialization methods
	 */
	void init(float nparticles, int xSize, int ySize, int zSize);
	void init2(float nparticles, int xSize, int ySize, int zSize);
	void sortParticles();
	Particle* getParticle(int index);
	std::vector<Particle> particles;
	/*
	 * This 2d vector tracks the starting locations for each box
	 * in the list of particles
	 * boxes that have no particles in them have -1 as their index;
	 */
	std::vector<std::vector<int> > indexTracker;

	int xSize, ySize, zSize;
	int numParticles;

	int carlSort(int value, int start);
	int carlYSort(int value, int start, int end);
	void shakerSort(int start, int end);

	int2 getParticlesListIndex(int3 boxID);

	int2 pseudoBinarySearch(int3 boxID);

	void initializeIndexTracker(int xSize, int ySize);
private:
};


#endif
