#include "ParticleCollection.h"

/*
 * Initialization Algorithms
 */
void ParticleCollection::init(float nparticles, int xSize, int ySize, int zSize)
{
	numParticles = nparticles;
	particles.resize(numParticles);
	this->xSize = xSize;
	this->ySize = ySize;
	this->zSize = zSize;
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

int2 ParticleCollection::getParticlesListIndex(int3 boxID){
	int2 ret;
	ret.x = 0;
	ret.y = 0;
	int i = 0;

	// Find the beginning of the list of the given boxID.
	for (i = 0; i < particles.size(); i++)
	{
		if(particles[i].boxID.x == boxID.x && particles[i].boxID.y == boxID.y && particles[i].boxID.z == boxID.z)
		{
			ret.x = i;
			break;
		}
	}

	// Find the end of the list at the given boxID.
	for (int j = i; j < particles.size(); j++)
	{
		if (particles[j].boxID.y != boxID.y && particles[j].boxID.x != boxID.x && particles[j].boxID.z != boxID.z)
		{
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
int2 ParticleCollection::pseudoBinarySearch(int3 boxID){

	// ---------------------------------------------------------------------
	// TODO: THIS CODE IS NOT BEING UPDATED TO ACCOUNT FOR A 3-VALUE boxID!!
	// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

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

int ParticleCollection::carlYSort(int value, int start, int end)
{
	int insert = start;
	for(int i = start; i < end; i++)
	{
		if(particles[i].boxID.y == value)
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
			if(particles[i-1].boxID.z > particles[i].boxID.z)
			{
				std::swap(particles[i], particles[i-1]);
				exchange = true;
			}
		}
		for(int i = start + 1; i < end; i++)
		{
			if(particles[i-1].boxID.z > particles[i].boxID.z)
			{
				std::swap(particles[i], particles[i-1]);
				exchange = true;
			}
		}
	} while(exchange);
}

void ParticleCollection::sortParticles()
{
	int xStart = 0; // The index of the start of the current x-values.
	int yStart = 0; // The index of the start of the current y-values.
	int xEnd = 0; // The index of the end of the current x-values.
	int yEnd = 0; // The index of the end of the current y-values.

	for(int x = 0; x < xSize; x++)
	{
		xEnd = carlSort(x, xStart); // carlSort will return the last index of the current x-values.
		for(int y = 0; y < ySize; y++)
		{
			yEnd = carlYSort(y, yStart, xEnd); // carlYSort will return the last index of the current y-values.
			shakerSort(yStart, yEnd); // shaker sort will sort the z-values at the given x,y values.
			yStart = yEnd;
		}
		xStart = xEnd;
	}
}
