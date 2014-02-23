#include "Physics.h" 
#include <iostream>

void Physics::init(Environment* envPointer){
	env = envPointer;
}

Vec2 Physics::interpolate(Vec2* a, Vec2* b, float offset)
{
	Vec2 ret;
	ret.x = offset*a->x + (1-offset)*b->x;
	ret.y = offset*a->y + (1-offset)*b->y;
    //ret.x = a->x + b->x;
	//ret.y = a->y + b->y;
	return ret;
}

Vec2 Physics::extrapolate(Vec2 velocity, float offset)
{
	Vec2 ret;
	ret.x = velocity.x; //* (1/offset);
	ret.y = velocity.y; //* (1/offset);
	return ret;
}

void Physics::updateGridForces()
{
    int index = 0; // The index of the current particle
    float xOffset, yOffset; // The distance between the particle at 'index'
                            // the upper xnode and upper ynode
    Vec2 position, velocity, newForce, xHighForce, xLowForce;
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
                
                // Set the offset values based on the upper bounds of the box.
                xOffset = (x+1) - position.x;
                yOffset = (y+1) - position.y;
                
                // Extrapolate the current particles forces along the x-axis.
                xHighForce = extrapolate(velocity, 1-xOffset);
                xLowForce = extrapolate(velocity, xOffset);
                
                // Extrapolate the force at xLowForce to the bottom left node of boxID.
                Node * node = &env -> grid.grid[x][y];
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

void Physics::updateParticlePositions()
{
	Vec2 position, velocity, newVelocity;
	for(int i = 0; i < env -> numParticles; i++)
	{
		Particle* cur;
		cur = env->particles.getParticle(i);
		position = cur -> getPosition();
		velocity = cur -> getVelocity();

		int lowX = fmax( floor(position.x), 0);
		int highX = fmin(ceil(position.x), env -> xSize - 1);
		int lowY = fmax( floor(position.y), 0);
		int highY = fmin( ceil(position.y), env -> ySize - 1 );

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

		//if(i == 300)
		//	std::cout << newVelocity.x << ", "<< velocity.y <<"\n";

		if(position.x + newVelocity.x <= 0 || position.x + newVelocity.x >= env -> xSize)
			newVelocity.x = -newVelocity.x;
		if(position.y + newVelocity.y <= 0 || position.y  + newVelocity.y >= env -> ySize)
			newVelocity.y = -newVelocity.y;

		cur -> setPosition(position.x + newVelocity.x, position.y + newVelocity.y);
		//cur -> setVelocity((velocity.x + position.x)/2.0f, (velocity.y + position.y)/2.0f);
		cur -> setVelocity(newVelocity.x, newVelocity.y);

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

void Physics::resetNodes(){
    for (int i = 0; i < env -> xSize; i++) {
        for (int j = 0; j < env -> ySize; j++) {
            env -> grid.grid[i][j].reset();
        }
    }
}


