#include "Environment.h"

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
			grid[x][y] = a;
			//forceY += 0.002f;
		}
		//forceX += 0.002f;
	}
}

void Environment::generateParticles()
{
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
		particles[i] = a;
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
