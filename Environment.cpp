#include "Environment.h"

Environment::Environment(){

}

void Environment::init(int x, int y, int numPs){
	xSize = x;
	ySize = y;
	particles.resize(numPs);
	numParticles = numPs;
	grid.init(x, y);
}

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
			//a.setForce(0.02, 0.02);
			grid.grid[x][y] = a;
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
		//xPos = rand()%xSize;
		//yPos = rand()%ySize;
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

int Environment::carlSort(int value, int start)
{
	int insert = start;
	Particle temp;

	for(int i = start; i < numParticles; i++)
	{
		if(particles[i].boxID.x == value)
		{
			temp = particles[i];
			particles[i] = particles[insert];
			particles[insert] = temp;
			insert++;
		}
	}
	return 0;
}

void Environment::shakerSort(int start, int end)
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
				temp = particles[i-1];
				particles[i-1] = particles[i];
				particles[i] = temp;
				exchange = true;
			}
		}
		for(int i = start + 1; i < end; i++)
		{
			if(particles[i-1].boxID.y > particles[i].boxID.y)
			{
				temp = particles[i-1];
				particles[i-1] = particles[i];
				particles[i] = temp;
				exchange = true;
			}
		}
	} while(exchange);
}

void Environment::sortParticles()
{
	int startIndex = 0; // The index of the start of the current values.
	int endIndex = 0; // The index of the end of the current values.

	for(int x = 0; x < xSize; x++)
	{
		endIndex = carlSort(x, startIndex); // carlSort will return the last index of the current x-values.
		//shakerSort(startIndex, endIndex);
		startIndex = endIndex + 1;
	}
}
