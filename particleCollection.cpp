#include "ParticleCollection.h"

/*
 * Initialization Algorithms
 */
void ParticleCollection::init(float nparticles, int xSize, int ySize){
    numParticles = nparticles;
    particles.resize(numParticles);
    this->xSize = xSize;
	for(int i = 0; i < numParticles; i++)
	{
		Particle a;
        a = Configs::random_confic_particles(xSize, ySize);
		particles[i] = a;
	}
}

/*
 * Getters and Setters
 */

Particle * ParticleCollection::getParticle(int index){
    return &particles[index];
}


/*
 * Sorting Algorithms
 */

int ParticleCollection::carlSort(int value, int start)
{
	int insert = start;
	for(int i = start; i < numParticles; i++)
	{
		if(particles[i].boxID.x == value)
		{
			std::swap(particles[i], particles[insert]);
			insert++;
		}
	}
	return insert;
}

void ParticleCollection::shakerSort(int start, int end)
{
	bool exchange;
	Particle temp;
	do
	{
		exchange = false;
		for(int i = end-1; i > start; i--)
		{
			if(particles[i-1].boxID.y > particles[i].boxID.y)
			{
				std::swap(particles[i], particles[i-1]);
				exchange = true;
			}
		}
		for(int i = start + 1; i < end; i++)
		{
			if(particles[i-1].boxID.y > particles[i].boxID.y)
			{
				std::swap(particles[i], particles[i-1]);
				exchange = true;
			}
		}
	} while(exchange);
}

void ParticleCollection::sortParticles()
{
	int startIndex = 0; // The index of the start of the current values.
	int endIndex = 0; // The index of the end of the current values.
    
	for(int x = 0; x < xSize; x++)
	{
		endIndex = carlSort(x, startIndex); // carlSort will return the last index of the current x-values.
		shakerSort(startIndex, endIndex);
		startIndex = endIndex;
	}
}
