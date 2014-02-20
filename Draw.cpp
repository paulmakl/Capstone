#include "Draw.h"

void Draw::init(Environment* envPointer){
	env = envPointer;
}

void Draw::displayGrid()
{
	glPointSize(1.0);
	glBegin(GL_POINTS);
	Vec4 color;
	for(int x = 0; x < env -> xSize; x++)
	{
		for(int y = 0; y < env -> ySize; y++)
		{
			Node* cur = &env->grid.grid[x][y];
			cur -> setForceColor();
			color = cur -> getRGBA();
			glColor3f(color.r, color.g, color.b);
			glVertex3f(x, y, 0);
		}
	}
	glEnd();
}

void Draw::displayParticles()
{
	glPointSize(1.0);
	Vec2 position, velocity;
	//glColor3f(1.0f, 1.0f, 1.0f);
	float color = 1.0f;
	glBegin(GL_POINTS);

	for(int i = 0; i < env -> numParticles; i++)
	{
		Particle* cur;
		cur = env->particles.getParticle(i);

		// NOTE: Delete the line below to fix the color.
		color -= 0.0001f;
		position = cur -> getPosition();
		velocity = cur -> getVelocity();
        float r = cur -> getColor().x;
        float g = cur -> getColor().y;
        float b = cur -> getColor().z;
		glColor3f(r, g, b);
		glVertex3f(position.x, position.y, 0);
	}
	glEnd();
}

void Draw::displayShapes()
{
	Vec3 position;

	for(int i = 0; i < numShapes; i++)
	{
		Cube* cur;
		cur = &env->shapes[i];
		position = cur -> getPosition();
		glTranslatef(position.x, position.y, position.z);
		glutWireCube(cur -> getLength());
	}
}
