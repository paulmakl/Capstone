/*
 * Particle.cpp
 *
 *  Created on: Feb 3, 2014
 *      Author: Etan
 */

class Particle
{
public:
	Vec2 position;
	Vec2 velocity;

	void setPosition(float x, float y)
	{
		position.x = x;
		position.y = y;
	}
	void setVelocity(float x, float y)
	{
		velocity.x = x;
		velocity.y = y;
	}
	Vec2 getVelocity()
	{
		return velocity;
	}
	Vec2 getPosition()
	{
		return position;
	}
};
