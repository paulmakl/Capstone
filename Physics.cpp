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
	return ret;
}

Vec2 Physics::extrapolate(Vec2 velocity, float offset)
{
	Vec2 ret;
	ret.x = velocity.x * 2 * offset;
	ret.y = velocity.y * 2 * offset;
	return ret;
}

void Physics::updateGridForces()
{
    int index = 0;
    float xOffset, yOffset;
    Vec2 position, velocity, newForce, xHighForce, xLowForce;
	// First reset all nodes to have no forces.
	for(int x = 0; x < env -> xSize-1; x++)
	{
		for(int y = 0; y < env -> ySize-1; y++)
		{
            Particle* cur = env -> particles.getParticle(index);

            while (cur -> boxID.x == x && cur -> boxID.y == y)
            {
                cur = env -> particles.getParticle(index);
                position = cur -> getPosition();
                velocity = cur -> getVelocity();
                
                //This is the distance from the higher x value;
                xOffset = (x+1) - position.x;
                yOffset = (y+1) - position.y;
                
                xHighForce = extrapolate(velocity, 1-xOffset);
                xLowForce = extrapolate(velocity, xOffset);
                
                Node * node = &env -> grid.grid[x][y];
                newForce = extrapolate(xLowForce, yOffset);
                node -> incForce(newForce.x, newForce.y);
                node -> incParticlesNearNode();
                
                node = &env -> grid.grid[x][y + 1];
                newForce = extrapolate(xLowForce, 1 - yOffset);
                node -> incForce(newForce.x, newForce.y);
                node -> incParticlesNearNode();
                
                node = &env -> grid.grid[x + 1][y];
                newForce = extrapolate(xLowForce, yOffset);
                node -> incForce(newForce.x, newForce.y);
                node -> incParticlesNearNode();
                
                node = &env -> grid.grid[x + 1][y + 1];
                newForce = extrapolate(xLowForce, 1 - yOffset);
                node -> incForce(newForce.x, newForce.y);
                node -> incParticlesNearNode();
                
                index++;
            }
		}
	}
}

void Physics::updateParticlePositions()
{
	Vec2 position, velocity;
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
		velocity = interpolate(&r1, &r2, yOffset);

		//velocity.x *= 3.8f;
		//velocity.y *= 3.8f;

		if(i == 300)
			std::cout << velocity.x << ", "<< velocity.y <<"\n";

		if(position.x + velocity.x <= 0 || position.x + velocity.x >= env -> xSize)
			velocity.x = 0;//-velocity.x;
		if(position.y + velocity.y <= 0 || position.y  + velocity.y >= env -> ySize)
			velocity.y = 0;//-velocity.y;

		cur -> setPosition(position.x + velocity.x, position.y + velocity.y);
		//cur -> setVelocity((velocity.x + position.x)/2.0f, (velocity.y + position.y)/2.0f);
		cur -> setVelocity(velocity.x, velocity.y);

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


