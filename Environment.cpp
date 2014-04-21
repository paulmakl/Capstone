#include "Environment.h"

/*
 * Initialization Code
 */

Environment::Environment(){
    
}

void Environment::init(int x, int y, int z, int numPs){
	xSize = x;
	ySize = y;
	zSize = z;
	particles.init(numPs, x, y, z);

//    for (int i = 0; i < numParticles; i++) {
//        c.addParticles(particles.getParticle(i));
//    }
	maxParticles = numPs;
	numParticles = 0;
	grid.init(x, y, z);
}

/*
 *Generating Environment Variables
 */
void Environment::generateNodes()
{
	int x, y, z;
	float r, g, b;
	float forceX, forceY;
	forceX = 0.0;//0.064;
	for(x = 0; x < xSize; x++)
	{
		forceY = 0.0f;
		for(y = 0; y < ySize; y++)
		{
			for(z = 0; z < zSize; z++)
			{
				Node a;
				r = 0.2f + rand()%30/100.0f;
				g = 0.2f + rand()%30/100.0f;
				b = 0.2f + rand()%30/100.0f;
				a.setRGBA(r, g, b, 1.0f);
				a.setForce(forceX + rand()%100/1000.0f - 0.055f, forceY + rand()%100/1000.0f - 0.055f, 0); //, rand()%100/1000.0f - 0.055f);
				grid.grid[x][y][z] = a;
			}
		}
	}
}

void Environment::generateShapes()
{
	//TODO: These are hard-coded shapes. We will read in information later to determine what shapes to draw.
	Vec3 location;
	location.x = xSize/2.0f;
	location.y = ySize/2.0f;
	location.z = 0.0f;
	float length = 10.0f;
	for(int i = 0; i < numShapes; i++)
	{
		Cube b;
		b.setVariables(length, location);
		shapes[i] = b;
	}
}

void Environment::sortParticles(){
	particles.sortParticles(numParticles);
}

void Environment::releaseParticles(int num)
{
	numParticles += num;
	if(numParticles > maxParticles)
		numParticles = maxParticles;
}

void Environment::injectParticles(int num)
{
	numParticles += num;
	maxParticles += num;
}
