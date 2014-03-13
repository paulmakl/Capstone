#include "ParticleCollection.h"

/*
 * Initialization Algorithms
 */
void ParticleCollection::init(float nparticles, int xSize, int ySize, int zSize)
{
    numParticles = nparticles;
    particles.resize(numParticles);
    this->xSize = xSize;
	for(int i = 0; i < numParticles; i++)
	{
		Particle a;
        a = Configs::random_confic_particles(xSize, ySize, zSize);
		//a = Configs::test_config_particles();
        a.name = i;
        particles[i] = a;
	}
    initializeIndexTracker(xSize, ySize);
}

void ParticleCollection::initializeIndexTracker(int xSize, int ySize){
    indexTracker.resize(xSize);
    for (int i = 0; i < ySize; i++) {
        indexTracker[i].resize(ySize);
    }
    for (int i = 0; i < indexTracker.size(); i++) {
        for (int j = 0; j < indexTracker[0].size(); j++) {
            indexTracker[i][j] = -1;
        }
    }
}

/*
 * Getters and Setters
 */

Particle * ParticleCollection::getParticle(int index){
    return &particles[index];
}

int2 ParticleCollection::getParticlesListIndex(int2 boxID){
    int2 ret;
    ret.x = 0;
    ret.y = 0;
    int i = 0;
    int j = 0;
    for (i = 0; i < particles.size(); i++) {
        if(particles[i].boxID.x == boxID.x && particles[i].boxID.y == boxID.y){
            ret.x = i;
            break;
        }
    }
    
    for (j = i; j < particles.size(); j++){
        if (particles[j].boxID.y != boxID.y && particles[j].boxID.x != boxID.x) {
            ret.y = j-1;
            break;
        }
    }
    
    
    
    return ret;
}

/*
 * Search Algorithms
 */

/*
 * returns an int2 a
 * a.x is the start of a box in the list of particles
 * a.y is the end index of the b    ox in the list of particles
 */
int2 ParticleCollection::pseudoBinarySearch(int2 boxID){
    int2 ret;
    int index = particles.size()/2;
    int temp = 0;
    while( index > 0 || index == particles.size() ){
        if (particles[index].boxID.x == boxID.x) {
            break;
        }else if(particles[index].boxID.x > boxID.x){
            temp = (particles.size() - index) / 2;
            index = fmin( index + temp, particles.size() );
        }else{
            index = fmax( (index-1) / 2, 0 );
        }
    }
    
    for (int i = index; i >= 0; i--) {
        if(particles[i].boxID.x != boxID.x && particles[i].boxID.y != boxID.y){
            ret.x = i;
            break;
        }
    }
    
    for (int i = index; i < particles.size(); i++) {
        if(particles[i].boxID.x != boxID.x && particles[i].boxID.y != boxID.y){
            ret.y = i;
            break;
        }
    }
    
    return ret;
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


