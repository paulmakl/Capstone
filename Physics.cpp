#include "Physics.h" 

/*Physics::Physics(Environment* envPointer){
	env = envPointer;
}*/

void Physics::temp(Environment* envPointer)
{
	env = envPointer;
}

Vec2 Physics::interpolate(Vec2 a, Vec2 b, float offset)
{
	Vec2 ret;
	ret.x = offset*a.x + (1-offset)*b.x;
	ret.y = offset*a.y + (1-offset)*b.y;
	return ret;
}

Vec2 Physics::extrapolate(Vec2 velocity, float offset)
{
	Vec2 ret;
	ret.x = velocity.x * offset;
	ret.y = velocity.y * offset;
	return ret;
}

void Physics::updateGridForces()
{
	// First reset all nodes to have no forces.
	for(int x = 0; x < xSize; x++)
	{
		for(int y = 0; y < ySize; y++)
		{
			env->grid[x][y].setForce(0.0f, 0.0f);
		}
	}
	Vec2 position, velocity, newForce;

	//Extrapolate particle movement to the nodes.
	for(int i = 0; i < numParticles; i++)
	{
		Particle* cur;
		cur = &env->particles[i];
		position = cur -> getPosition();
		velocity = cur -> getVelocity();

		int lowX = floor(position.x);
		int highX = ceil(position.x);
		int lowY = floor(position.y);
		int highY = ceil(position.y);

		float xOffset = highX - position.x;
		float yOffset = highY - position.y;

		Vec2 xHighForce = extrapolate(velocity, xOffset);
		Vec2 xLowForce = extrapolate(velocity, (1-xOffset));

		Node* node;

		node = &env->grid[lowX][lowY];
		newForce = extrapolate(xLowForce, (1-yOffset));
		node -> setForce(newForce.x, newForce.y);

		node = &env->grid[lowX][highY];
		newForce = extrapolate(xLowForce, yOffset);
		node -> setForce(newForce.x, newForce.y);

		node = &env->grid[highX][lowY];
		newForce = extrapolate(xHighForce, (1-yOffset));
		node -> setForce(newForce.x, newForce.y);

		node = &env->grid[highX][highY];
		newForce = extrapolate(xHighForce, (yOffset));
		node -> setForce(newForce.x, newForce.y);
	}
}

void Physics::updateParticlePositions()
{
	Vec2 position, velocity;
	for(int i = 0; i < numParticles; i++)
	{
		Particle* cur;
		cur = &env->particles[i];
		position = cur -> getPosition();
		velocity = cur -> getVelocity();

		int lowX = floor(position.x);
		int highX = ceil(position.x);
		int lowY = floor(position.y);
		int highY = ceil(position.y);

		Vec2 downLeftForce = env->grid[lowX][lowY].force;
		Vec2 downRightForce = env->grid[highX][lowY].force;
		Vec2 upLeftForce = env->grid[lowX][highY].force;
		Vec2 upRightForce = env->grid[highX][highY].force;

		float xOffset = highX - position.x;
		float yOffset = highY - position.y;

		Vec2 r1 = interpolate(downLeftForce, downRightForce, xOffset);
		Vec2 r2 = interpolate(upLeftForce, upRightForce, xOffset);
		velocity = interpolate(r1, r2, yOffset);

		if(position.x + velocity.x <= 0 || position.x + velocity.x >= xSize)
			velocity.x = -velocity.x;
		if(position.y + velocity.y <= 0 || position.y  + velocity.y >= ySize)
			velocity.y = -velocity.y;

		cur -> setPosition(position.x + velocity.x, position.y + velocity.y);
		cur -> setVelocity(velocity.x, velocity.y);
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
		if(floor(position.x - offset) < 0.0f || ceil(position.x + offset) > xSize ||
					floor(position.y - offset) < 0.0f || ceil(position.y + offset) > ySize)
		{
			return;
		}
		for(int x = floor(position.x - offset); x <= ceil(position.x + offset); x++)
		{
			for(int y = floor(position.y - offset); y <= ceil(position.y + offset); y++)
			{
				env->grid[x][y].setRGBA(1.0f, 0.0f, 0.0f, 1.0f);
			}
		}
	}
}
