#include "Physics.h" 
#include <iostream>

void Physics::init(Environment* envPointer)
{
	env = envPointer;
}

Vec2 Physics::interpolate(Vec2* a, Vec2* b, float offset)
{
	Vec2 ret;
	ret.x = offset*a -> x + (1-offset)*b -> x;
	ret.y = offset*a -> y + (1-offset)*b -> y;
	return ret;
}

Vec2 Physics::extrapolate(Vec2 velocity, float offset)
{
	Vec2 ret;
	ret.x = velocity.x;
	ret.y = velocity.y;
	return ret;
}

void Physics::updateGridForces()
{
	int index = 0; // The index of the current particle
	float xOffset, yOffset; // The distance between the particle at 'index'
	// the upper xnode and upper ynode
	Vec2 position, velocity, newForce, xHighForce, xLowForce;
	float mass;
	// Go through every valid box on the grid.
	// A box is vaid if the lower left corner is between
	// 0 and size - 1.
	for(int x = 0; x < env -> xSize-1; x++)
	{
		for(int y = 0; y < env -> ySize-1; y++)
		{
			// Get the particle to check the boxID the first run-through.
			Particle* cur = env -> particles.getParticle(index);

			// While we are in the same box...
			while (cur -> boxID.x == x && cur -> boxID.y == y)
			{
				// Get values for the current particle.

				position = cur -> getPosition();
				velocity = cur -> getVelocity();
				mass = cur -> getMass();

				// Set the offset values based on the upper bounds of the box.
				xOffset = (x+1) - position.x;
				yOffset = (y+1) - position.y;

				// Extrapolate the current particles forces along the x-axis.
				Vec2 momentum;
				momentum.x = (1-mass) * velocity.x;
				momentum.y = (1-mass) * velocity.y;
				xHighForce = extrapolate(momentum, 1-xOffset);
				xLowForce = extrapolate(momentum, xOffset);

				// Extrapolate the force at xLowForce to the bottom left node of boxID.
				Node* node = &env -> grid.grid[x][y];
				newForce = extrapolate(xLowForce, yOffset);
				node -> incForce(newForce.x, newForce.y);
				node -> incParticlesNearNode();

				// Extrapolate the force at xLowForce to the upper left node of boxID.
				node = &env -> grid.grid[x][y + 1];
				newForce = extrapolate(xLowForce, 1 - yOffset);
				node -> incForce(newForce.x, newForce.y);
				node -> incParticlesNearNode();

				// Extrapolate the force at xHighForce to the upper right node of boxID.
				node = &env -> grid.grid[x + 1][y];
				newForce = extrapolate(xLowForce, yOffset);
				node -> incForce(newForce.x, newForce.y);
				node -> incParticlesNearNode();

				// Extrapolate the force at xHighForce to the upper left node of boxID.
				node = &env -> grid.grid[x + 1][y + 1];
				newForce = extrapolate(xLowForce, 1 - yOffset);
				node -> incForce(newForce.x, newForce.y);
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


void Physics::updateParticleVelocities()
{
	Vec2 position, velocity, newVelocity;
	Particle* cur;
	for(int i = 0; i < env -> numParticles; i++)
	{
		cur = env->particles.getParticle(i);
		position = cur -> getPosition();
		velocity = cur -> getVelocity();

		int lowX = fmax( floor(position.x), 0);
		int highX = fmin(ceil(position.x), env -> xSize - 1);
		int lowY = fmax( floor(position.y), 0);
		int highY = fmin( ceil(position.y), env -> ySize - 1);

		Vec2 downLeftForce = env->grid.grid[lowX][lowY].getForce();
		Vec2 downRightForce = env->grid.grid[highX][lowY].getForce();
		Vec2 upLeftForce = env->grid.grid[lowX][highY].getForce();
		Vec2 upRightForce = env->grid.grid[highX][highY].getForce();

		float xOffset = highX - position.x;
		float yOffset = highY - position.y;

		Vec2 r1 = interpolate(&downLeftForce, &downRightForce, xOffset);
		Vec2 r2 = interpolate(&upLeftForce, &upRightForce, xOffset);
		newVelocity = interpolate(&r1, &r2, yOffset);


		// Apply particle's mass to maintain momentum.
		float mass = cur -> getMass();
		newVelocity.x = (newVelocity.x*(1.0f - mass) + (velocity.x * mass));
		newVelocity.y = (newVelocity.y*(1.0f - mass) + (velocity.y * mass));

		if(position.x + newVelocity.x <= 0 || position.x + newVelocity.x >= env -> xSize - 1)
		{
			//newVelocity.x = 0;
			//newVelocity.y = 0;
			newVelocity.x = -newVelocity.x;
		}
		if(position.y + newVelocity.y <= 0 || position.y  + newVelocity.y >= env -> ySize - 1)
		{
			//newVelocity.x = 0;
			//newVelocity.y = 0;
			newVelocity.y = -newVelocity.y;
		}
		cur -> setVelocity(newVelocity.x, newVelocity.y);
        
        //Based on the new velocity, we calculate the new position
        Vec2 bNewPosition;
        bNewPosition.x = cur -> position.x + newVelocity.x;
        bNewPosition.y = cur -> position.y + newVelocity.y;
        cur -> nextPosition = bNewPosition;
        
	}
}

float Physics::calculateDistance(Vec2 a, Vec2 b)
{
	return pow(a.x - b.x, 2) + pow(a.y - b.y, 2);
}

void Physics::checkParticleCollisions()
{
	for(int i = 0; i < env -> numParticles; i++)
	{
        Particle* cur = env -> particles.getParticle(i);
        checkParticlecollisionsAtIndex(i, cur -> boxID);
        if(cur -> nextBoxID.x != cur -> boxID.x || cur -> nextBoxID.y != cur -> boxID.y){
            checkParticlecollisionsAtIndex(i, cur -> nextBoxID);
        }
	}
}

void Physics::checkParticlecollisionsAtIndex(int i, int2 boxID){
    Particle* ballistic; // The particle we are checking to see if it collides with other particles.
	Particle* target; // The target particle we are checking collision with.
    
    ballistic = env -> particles.getParticle(i);
    target = env -> particles.getParticle(i);
    
    int2 boxListIndex = env -> particles.getParticlesListIndex(boxID);
    //int2 boxListIndex = env -> particles.pseudoBinarySearch(boxID);
    //std::cout << boxListIndex.x << " " << boxListIndex.y;
    //for(int j = i+1; j <= env -> numParticles; j++)
    for(int j = boxListIndex.x; j < boxListIndex.y; j++)
    //for(int j = env -> particles.indexTracker[boxID.x][boxID.y]; target -> boxID.x == boxID.x && target -> boxID.x ==boxID.y; j++)
    {
        target = env -> particles.getParticle(j);
        if(target->name != ballistic->name){
            Vec2 bVelocity, tVelocity;
            bVelocity = ballistic -> getVelocity();
            tVelocity = target -> getVelocity();
            
            Vec2 bPosition, tPosition;
            bPosition = ballistic -> getPosition();
            tPosition = target -> getPosition();
            
            // Calculate the distance between the ballistic and target particles.
            float distanceBetweenParticles = calculateDistance(bPosition, tPosition);
            
            Vec2 bNewPosition, tNewPosition;
            bNewPosition.x = bPosition.x + bVelocity.x;
            tNewPosition.x = tPosition.x + tVelocity.x;
            bNewPosition.y = bPosition.y + bVelocity.y;
            tNewPosition.y = tPosition.y + tVelocity.y;
            
            float bDistance = calculateDistance(bPosition, bNewPosition);
            float tDistance = calculateDistance(tPosition, tNewPosition);
            
            if(distanceBetweenParticles < bDistance + tDistance)
            {
                ballistic -> setColor(1.0f, 0.0f, 0.0f);
                target -> setColor(1.0f, 0.0f, 0.0f);
                
                float newX = (bVelocity.x + tVelocity.x)/2;
                float newY = (bVelocity.y + tVelocity.y)/2;
                
                ballistic -> setVelocity(newX, newY);
                target -> setVelocity(newX, newY);
                
                ballistic -> setMass(0.0f);
                target -> setMass(0.0f);
            }
        }

    }
}

void Physics::updateParticlePositions()
{
	Particle* cur;
	for(int i = 0; i < env -> numParticles; i++)
	{
		cur = env->particles.getParticle(i);
		cur -> moveFromVelocity();
	}
}

void Physics::addRandomVelocity()
{
	Particle* cur;
	for(int i = 0; i < env -> numParticles; i++)
	{
		cur = env->particles.getParticle(i);
		Vec2 velocity = cur-> getVelocity();
		velocity.x += (rand()%100)/10000.0f - 0.0054f;
		velocity.y += (rand()%100)/10000.0f - 0.0054f;

		cur->setVelocity(velocity.x, velocity.y);
	}
}

void Physics::gravity()
{
	Particle* cur;
	for(int i = 0; i < env -> numParticles; i++)
	{
		cur = env->particles.getParticle(i);
		Vec2 velocity = cur-> getVelocity();
		velocity.y -= (2.0f - cur -> getMass()) * force_gravity;

		cur->setVelocity(velocity.x, velocity.y);
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
				env->grid.grid[x][y].setRGBA(1.0f, 0.0f, 0.0f, 1.0f);
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
			env -> grid.grid[i][j].reset();
		}
	}
}


