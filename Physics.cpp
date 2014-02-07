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

void Physics::updatePositions()
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
		cur -> setVelocity((velocity.x + position.x)/2.0f, (velocity.y + position.y)/2.0f);
	}
}
