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
			Node cur = env->grid.grid[x][y];
			color = cur.getRGBA();
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
	float color = 0.0f;
	glBegin(GL_POINTS);

	for(int i = 0; i < env -> numParticles; i++)
	{
		color = ((float)(rand()%(i+1)))/((float)(env -> numParticles));
		Particle* cur;
		cur = &env->particles[i];
		position = cur -> getPosition();
		velocity = cur -> getVelocity();
		glColor3f(color, color, color);
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
