#include "ParticleCollection.h"

/*
 * Initialization Algorithms
 */
void ParticleCollection::init(float nparticles, int xSize, int ySize){
    numParticles = nparticles;
    particles.resize(numParticles);
    float xVelo, yVelo, xPos, yPos;
	for(int i = 0; i < numParticles; i++)
	{
		Particle a;
		xPos = (float)(rand()%(xSize*100)) / 100.0f;
		yPos = (float)(rand()%(ySize*100)) / 100.0f;
        
		a.setPosition(xPos, yPos);
        
		xVelo = (rand()%10)/1000.0f - 0.0055f;
		yVelo = (rand()%10)/1000.0f - 0.0055f;
		a.setVelocity(xVelo, yVelo);
        a.setColor( 1.0f, 0.0f, 0.0f );
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
				/*temp = particles[i-1];
                 particles[i-1] = particles[i];
                 particles[i] = temp;*/
				std::swap(particles[i], particles[i-1]);
				exchange = true;
			}
		}
		for(int i = start + 1; i < end; i++)
		{
			if(particles[i-1].boxID.y > particles[i].boxID.y)
			{
				/*temp = particles[i-1];
                 particles[i-1] = particles[i];
                 particles[i] = temp;*/
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
    
	for(int x = 0; x < gridwitdh; x++)
	{
		endIndex = carlSort(x, startIndex); // carlSort will return the last index of the current x-values.
		shakerSort(startIndex, endIndex);
		startIndex = endIndex + 1;
	}
}