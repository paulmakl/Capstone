#include "Draw.h"

/*Draw::Draw(Environment* envPointer){
	env = envPointer;
}*/

void Draw::temp(Environment* envPointer)
{
	env = envPointer;
}

void Draw::displayGrid()
{
	glPointSize(1.0);
	glBegin(GL_POINTS);
	Vec4 color;
	for(int x = 0; x < xSize; x++)
	{
		for(int y = 0; y < ySize; y++)
		{
			Node cur = env->grid[x][y];
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
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_POINTS);

	for(int i = 0; i < numParticles; i++)
	{
		Particle* cur;
		cur = &env->particles[i];
		position = cur -> getPosition();
		velocity = cur -> getVelocity();
		glVertex3f(position.x, position.y, 0);
	}
	glEnd();
}
