#include "Environment.h"

/*
 * Initialization Code
 */

Environment::Environment(){

}

void Environment::init(int x, int y, int numPs){
	xSize = x;
	ySize = y;
	particles.init(numPs, x, y);
	numParticles = numPs;
	grid.init(x, y);
}

/*
 *Generating Environment Variables
 */

void Environment::generateNodes()
{
	int x, y;
	float r, g, b;
	float forceX, forceY;
	forceX = 0.0;//0.064;
	for(x = 0; x < xSize; x++)
	{
		forceY = 0.0f;
		for(y = 0; y < ySize; y++)
		{
			Node a;
			r = 0.2f + rand()%30/100.0f;
			g = 0.2f + rand()%30/100.0f;
			b = 0.2f + rand()%30/100.0f;
			a.setRGBA(r, g, b, 1.0f);
			a.setForce(forceX + rand()%100/1000.0f - 0.055f, forceY + rand()%100/1000.0f - 0.055f); //, rand()%100/1000.0f - 0.055f);
			grid.grid[x][y] = a;
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
    particles.sortParticles();
}

