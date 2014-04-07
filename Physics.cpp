#include "Physics.h" 
#include <iostream>

#define COLLIDED_COLOR 1.0f, 0.1f, 0.1f

/**
 * Sets the environment pointer that the physics will be working with.
 */
void Physics::init(Environment* envPointer)
{
	env = envPointer;
}

Vec3 Physics::interpolate(Vec3* a, Vec3* b, float offset)
{
	Vec3 ret;
	ret.x = offset*a -> x + (1-offset)*b -> x;
	ret.y = offset*a -> y + (1-offset)*b -> y;
	ret.z = offset*a -> z + (1-offset)*b -> z;
	return ret;
}

Vec3 Physics::extrapolate(Vec3 velocity, float offset)
{
	Vec3 ret;
	ret.x = velocity.x;
	ret.y = velocity.y;
	ret.z = velocity.z;
	return ret;
}

/**
 * Extrapolates every particle's force onto the neighboring nodes of the grid.
 */
void Physics::updateGridForces()
{
	int index = 0; // The index of the current particle
	float xOffset, yOffset, zOffset; // The distance between the particle at 'index'
	// the upper xnode and upper ynode
	Vec3 newForce, xHighForce, xLowForce;
	Vec3 xHigh_yHigh_Force, xHigh_yLow_Force, xLow_yHigh_Force, xLow_yLow_Force;
	Vec3 position, velocity;
	float mass;
	// Go through every valid box on the grid.
	// A box is valid if the lower left corner is between
	// 0 and size - 1.
	for(int x = 0; x < env -> xSize-1; x++)
	{
		for(int y = 0; y < env -> ySize-1; y++)
		{
			for(int z = 0; z < env -> zSize-1; z++)
			{
				// Get the particle to check the boxID the first run-through.
				Particle* cur = env -> particles.getParticle(index);

				// While we are in the same box...
				while (cur -> boxID.x == x && cur -> boxID.y == y && cur -> boxID.z == z)
				{

					// Get values for the current particle.
					position = cur -> getPosition();
					velocity = cur -> getVelocity();
					mass = cur -> getMass();

					// Set the offset values based on the upper bounds of the box.
					xOffset = (x+1) - position.x;
					yOffset = (y+1) - position.y;
					zOffset = (z+1) - position.z;

					// Extrapolate the current particles forces along the x-axis.
					Vec3 momentum;
					momentum.x = (1-mass) * velocity.x;
					momentum.y = (1-mass) * velocity.y;
					momentum.z = (1-mass) * velocity.z;
					xHighForce = extrapolate(momentum, 1-xOffset);
					xLowForce = extrapolate(momentum, xOffset);

					// Extrapolate the current particle's force at xHigh and xLow along the y-axis.
					xHigh_yLow_Force = extrapolate(xHighForce, yOffset); // upper right
					xHigh_yHigh_Force = extrapolate(xHighForce, 1 - yOffset); // upper right
					xLow_yLow_Force = extrapolate(xLowForce, yOffset); // bottom left
					xLow_yHigh_Force = extrapolate(xLowForce, 1 - yOffset); // upper left

					// Extrapolate the force at xLow_yLow to z.
					Node* node = &env -> grid.grid[x][y][z];
					newForce = extrapolate(xLow_yLow_Force, zOffset);
					node -> incForce(newForce.x, newForce.y, newForce.z);
					node -> incParticlesNearNode();

					node = &env -> grid.grid[x][y][z + 1];
					newForce = extrapolate(xLow_yLow_Force, 1 - zOffset);
					node -> incForce(newForce.x, newForce.y, newForce.z);
					node -> incParticlesNearNode();

					// Extrapolate the force at xLow_yHigh to z.
					node = &env -> grid.grid[x][y + 1][z];
					newForce = extrapolate(xLow_yHigh_Force, zOffset);
					node -> incForce(newForce.x, newForce.y, newForce.z);
					node -> incParticlesNearNode();

					node = &env -> grid.grid[x][y + 1][z + 1];
					newForce = extrapolate(xLow_yHigh_Force, 1 - zOffset);
					node -> incForce(newForce.x, newForce.y, newForce.z);
					node -> incParticlesNearNode();

					// Extrapolate the force at xHigh_yLow to z.
					node = &env -> grid.grid[x + 1][y][z];
					newForce = extrapolate(xHigh_yLow_Force, zOffset);
					node -> incForce(newForce.x, newForce.y, newForce.z);
					node -> incParticlesNearNode();

					node = &env -> grid.grid[x + 1][y][z + 1];
					newForce = extrapolate(xHigh_yLow_Force, 1 - zOffset);
					node -> incForce(newForce.x, newForce.y, newForce.z);
					node -> incParticlesNearNode();

					// Extrapolate the force at xHigh_yHigh to z.
					node = &env -> grid.grid[x + 1][y + 1][z];
					newForce = extrapolate(xHigh_yHigh_Force, zOffset);
					node -> incForce(newForce.x, newForce.y, newForce.z);
					node -> incParticlesNearNode();

					node = &env -> grid.grid[x + 1][y + 1][z + 1];
					newForce = extrapolate(xHigh_yHigh_Force, 1 - zOffset);
					node -> incForce(newForce.x, newForce.y, newForce.z);
					node -> incParticlesNearNode();

					if(env -> numParticles > index)
					{
						index++; // Increment the index to move to the next particle.
						cur = env -> particles.getParticle(index);
					}
					else
					{
						break;
					}
				}
			}
		}
	}
}

void Physics::updateParticleVelocities()
{
	Vec3 velocity, newVelocity, position;
	Particle* cur;
	for(int i = 0; i < env -> numParticles; i++)
	{
		cur = env->particles.getParticle(i);
		position = cur -> getPosition();
		velocity = cur -> getVelocity();

		int lowX = fmax(floor(position.x), 0);
		int highX = fmin(ceil(position.x), env -> xSize - 1);
		int lowY = fmax(floor(position.y), 0);
		int highY = fmin(ceil(position.y), env -> ySize - 1);
		int lowZ = fmax(floor(position.z), 0);
		int highZ = fmin(ceil(position.z), env -> zSize - 1);

		// Uppercase letter = higher, lowercase letter = lower
		Vec3 force_xyz = env -> grid.grid[lowX][lowY][lowZ].getForce();
		Vec3 force_Xyz = env -> grid.grid[highX][lowY][lowZ].getForce();
		Vec3 force_xYz = env -> grid.grid[lowX][highY][lowZ].getForce();
		Vec3 force_XYz = env -> grid.grid[highX][highY][lowZ].getForce();
		Vec3 force_xyZ = env -> grid.grid[lowX][lowY][highZ].getForce();
		Vec3 force_XyZ = env -> grid.grid[highX][lowY][highZ].getForce();
		Vec3 force_xYZ = env -> grid.grid[lowX][highY][highZ].getForce();
		Vec3 force_XYZ = env -> grid.grid[highX][highY][highZ].getForce();

		float xOffset = highX - position.x;
		float yOffset = highY - position.y;
		float zOffset = highZ - position.z;

		// Interpolate along the x-axis for high and low z-values.
		Vec3 r1 = interpolate(&force_xyz, &force_Xyz, xOffset);
		Vec3 r2 = interpolate(&force_xYz, &force_XYz, xOffset);
		Vec3 r3 = interpolate(&force_xyZ, &force_XyZ, xOffset);
		Vec3 r4 = interpolate(&force_xYZ, &force_XYZ, xOffset);

		// Interpolate between the r-interpolations.
		Vec3 s1 = interpolate(&r1, &r2, yOffset);
		Vec3 s2 = interpolate(&r3, &r4, yOffset);

		// Interpolate between the s-interpolations. This is the final velocity for the particle.
		newVelocity = interpolate(&s1, &s2, zOffset);

		// Apply particle's mass to maintain momentum.
		float mass = cur -> getMass();
		newVelocity.x = (newVelocity.x*(1.0f - mass) + (velocity.x * mass));
		newVelocity.y = (newVelocity.y*(1.0f - mass) + (velocity.y * mass));
		newVelocity.z = (newVelocity.z*(1.0f - mass) + (velocity.z * mass));

		if(position.x + newVelocity.x <= 0 || position.x + newVelocity.x >= env -> xSize - 1)
		{
			newVelocity.x = 0;
			newVelocity.y = 0;
			newVelocity.z = 0;
			//newVelocity.x = -newVelocity.x;
			cur -> setColor(COLLIDED_COLOR);
		}
		if(position.y + newVelocity.y <= 0 || position.y  + newVelocity.y >= env -> ySize - 1)
		{
			newVelocity.x = 0;
			newVelocity.y = 0;
			newVelocity.z = 0;
			//newVelocity.y = -newVelocity.y;
			cur -> setColor(COLLIDED_COLOR);
		}
		if(position.z + newVelocity.z <= 0 || position.z  + newVelocity.z >= env -> zSize - 1)
		{
			newVelocity.x = 0;
			newVelocity.y = 0;
			newVelocity.z = 0;
			//newVelocity.z = -newVelocity.z;
			cur -> setColor(COLLIDED_COLOR);
		}

		cur -> setVelocity(newVelocity.x, newVelocity.y, newVelocity.z);

		//Based on the new velocity, we calculate the new position
		Vec3 bNewPosition;
		bNewPosition.x = cur -> position.x + newVelocity.x;
		bNewPosition.y = cur -> position.y + newVelocity.y;
		bNewPosition.z = cur -> position.z + newVelocity.z;
		cur -> nextPosition = bNewPosition;
	}
}

/**
 * Returns the squared distance between two points.
 */
Vec3 Physics::calculateDistance(Vec3 a, Vec3 b)
{
	Vec3 ret;
	ret.x = pow(a.x - b.x, 2);
	ret.y = pow(a.y - b.y, 2);
	ret.z = pow(a.z - b.z, 2);
	return ret;
}

void Physics::checkParticleCollisions()
{
	for(int i = 0; i < env -> numParticles; i++)
	{
		Particle* cur = env -> particles.getParticle(i);
		//std::cout << "A " << cur -> boxID.x << " " << cur -> boxID.y << " " << cur -> boxID.z << "\n";
		checkParticlecollisionsAtIndex(i, cur -> boxID);

		if(cur -> nextBoxID.x != cur -> boxID.x || cur -> nextBoxID.y != cur -> boxID.y || cur -> nextBoxID.z != cur -> boxID.z)
		{
			//std::cout << "B " << cur -> boxID.x << " " << cur -> boxID.y << " " << cur -> boxID.z << "\n";
			//std::cout << "B NEXT " << cur -> nextBoxID.x << " " << cur -> nextBoxID.y << " " << cur -> nextBoxID.z << "\n";

			checkParticlecollisionsAtIndex(i, cur -> nextBoxID);
		}
	}
}

void Physics::checkParticlecollisionsAtIndex(int i, int3 boxID)
{
	Particle* ballistic; // The particle we are checking to see if it collides with other particles.
	Particle* target; // The target particle we are checking collision with.

	ballistic = env -> particles.getParticle(i);

	int2 boxListIndex = env -> particles.getParticlesListIndex(boxID);
	//int2 boxListIndex = env -> particles.pseudoBinarySearch(boxID);
	//std::cout << boxListIndex.x << " " << boxListIndex.y << "\n";
	//std::cout << boxID.x << " " << boxID.y << " " << boxID.z << "\n";
	//for(int j = i+1; j <= env -> numParticles; j++)
	for(int j = boxListIndex.x; j < boxListIndex.y; j++)
	{
		target = env -> particles.getParticle(j);

		// Check that the particle is not being compared to itself.
		if(target -> name != ballistic -> name)
		{
			Vec3 bVelocity, tVelocity;
			bVelocity = ballistic -> getVelocity();
			tVelocity = target -> getVelocity();

			Vec3 bPosition, tPosition;
			bPosition = ballistic -> getPosition();
			tPosition = target -> getPosition();

			// Calculate the distance between the ballistic and target particles.
			Vec3 distanceVector = calculateDistance(bPosition, tPosition);
			float distanceBetweenParticles = distanceVector.x + distanceVector.y + distanceVector.z;

			Vec3 bNewPosition, tNewPosition;
			bNewPosition.x = bPosition.x + bVelocity.x;
			tNewPosition.x = tPosition.x + tVelocity.x;
			bNewPosition.y = bPosition.y + bVelocity.y;
			tNewPosition.y = tPosition.y + tVelocity.y;
			bNewPosition.z = bPosition.z + bVelocity.z;
			tNewPosition.z = tPosition.z + tVelocity.z;

			Vec3 bDistance = calculateDistance(bPosition, bNewPosition);
			Vec3 tDistance = calculateDistance(tPosition, tNewPosition);

			/*if(distanceBetweenParticles < bDistance + tDistance)
			{
				ballistic -> setColor(COLLIDED_COLOR);
				target -> setColor(COLLIDED_COLOR);

				float newX = (bVelocity.x + tVelocity.x)/2;
				float newY = (bVelocity.y + tVelocity.y)/2;
				float newZ = (bVelocity.z + tVelocity.z)/2;

				ballistic -> setVelocity(newX, newY, newZ);
				target -> setVelocity(newX, newY, newZ);

				ballistic -> setVelocity(-bVelocity.x, -bVelocity.y, -bVelocity.z);
				target -> setVelocity(-tVelocity.x, -tVelocity.y, -tVelocity.z);

				ballistic -> setMass(0.3f);
				target -> setMass(0.3f);
			}*/

			/*
			 * Particles are occupying the same space.
			 */
			if(distanceBetweenParticles < ballistic -> getVolume() + target -> getVolume())
			{
				ballistic -> setColor(COLLIDED_COLOR);
				target -> setColor(COLLIDED_COLOR);

				float newX = (bVelocity.x + tVelocity.x)/2;
				float newY = (bVelocity.y + tVelocity.y)/2;
				float newZ = (bVelocity.z + tVelocity.z)/2;

				//ballistic -> setVelocity(newX, newY, newZ);
				//target -> setVelocity(newX, newY, newZ);

				//target -> changePosition(0.0f, 0.1f, 0.0f);
				ballistic-> changePosition(-distanceVector.x*0.5f, -distanceVector.y*0.5f, -distanceVector.z*0.5f);

			//	ballistic -> setVelocity(0.0f, 0.0f, 0.0f);
			//	target -> setVelocity(0.0f, 0.0f, 0.0f);


				ballistic -> setMass(0.01f);
				target -> setMass(0.01f);
			}
		}
	}
}

void Physics::updateParticlePositions()
{
	Particle* cur;
	for(int i = 0; i < env -> numParticles; i++)
	{
		cur = env -> particles.getParticle(i);
		Vec3 position = cur -> getPosition();

	/*	if(position.x < 0.0f)
			position.x = 0.0f;
		else if (position.x > env -> xSize - 1)
			position.x = env -> xSize - 1;
		if(position.y < 0.0f)
			position.y = 0.0f;
		else if(position.y > env -> ySize - 1)
			position.y = env -> ySize - 1;
		if(position.z < 0.0f)
			position.z = 0.0f;
		else if(position.z > env -> zSize - 1)
			position.z = env -> zSize - 1;*/

		cur -> moveFromVelocity();
	}
}

void Physics::addRandomVelocity(int index)
{
	//if(index < env -> numParticles && index >= 0)
	{
		index = rand()% env -> numParticles;
		Particle* cur;
		cur = env->particles.getParticle(index);
		Vec3 velocity = cur-> getVelocity();
		velocity.y -= (rand()%100)/100.0f;
		//cur -> changePosition(0.0f, -1.0f, 0.0f);
		cur->setVelocity(velocity.x, velocity.y, velocity.z);
	}
}

void Physics::gravity()
{
	Particle* cur;
	for(int i = 0; i < env -> numParticles; i++)
	{
		cur = env->particles.getParticle(i);
		Vec3 velocity = cur -> getVelocity();
		velocity.y -= (2.0f) * force_gravity;

		cur -> setVelocity(velocity.x, velocity.y, velocity.z);
	}
}

void Physics::updateShapePositions()
{
	Cube* cur;
	for(int i = 0; i < numShapes; i++)
	{
		cur = &env->shapes[i];
		Vec3 position = cur->getPosition();
		position.x += rand()%100/1000.0f - 0.055f;
		position.y += rand()%100/1000.0f - 0.055f;
		cur -> setPosition(position);
	}
}

void Physics::checkEulerianCollisions()
{
	Cube* cur;
	for(int i = 0; i < numShapes; i++)
	{
		cur = &env->shapes[i];
		Vec3 position = cur->getPosition();
		float length = cur->getLength();
		float offset = length/2.0f; // The distance from the center of the cube to any edge (half the length).
		if(floor(position.x - offset) < 0.0f || ceil(position.x + offset) > env -> xSize ||
				floor(position.y - offset) < 0.0f || ceil(position.y + offset) > env -> ySize)
		{
			return;
		}
		for(int x = floor(position.x - offset); x <= ceil(position.x + offset); x++)
		{
			for(int y = floor(position.y - offset); y <= ceil(position.y + offset); y++)
			{
				for(int z = floor(position.z - offset); y <= ceil(position.z + offset); y++)
				{
					env->grid.grid[x][y][z].setRGBA(1.0f, 0.0f, 0.0f, 1.0f);
				}
			}
		}
	}
}

void Physics::resetNodes()
{
	for (int i = 0; i < env -> xSize; i++)
	{
		for (int j = 0; j < env -> ySize; j++)
		{
			for(int k = 0; k < env -> zSize; k++)
			{
				env -> grid.grid[i][j][k].reset();
			}
		}
	}
}


