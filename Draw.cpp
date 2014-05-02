#include "Draw.h"

void Draw::init(Environment* envPointer){
	env = envPointer;
}

void Draw::displayGrid()
{
	glPointSize(2.0);
	glBegin(GL_POINTS);
	Vec4 color;
	for(int x = 0; x < env -> xSize; x++)
	{
		for(int y = 0; y < env -> ySize; y++)
		{
			for(int z = 0; z < env -> zSize; z++)
			{
				Node* cur = &env->grid.grid[x][y][z];
				cur -> setForceColor();
				color = cur -> getRGBA();
				float alpha = 0.2f;
				//if(color.r + color.g + color.b > 0)
				alpha = 1.0f;
				glColor4f(color.r, color.g, color.b, alpha);
				glVertex3f(x, y, z);
			}
		}
	}
	glEnd();
}

void Draw::displayParticles()
{
	//glPointSize(1.0);
	Vec3 position;
	//glColor3f(1.0f, 1.0f, 1.0f);
	float color = 1.0f;

	for(int i = 0; i < env -> numParticles; i++)
	{
		Particle* cur;
		cur = env->particles.getParticle(i);

		position = cur -> getPosition();
		float colorScale = 0.1f + (float)(env -> zSize - position.z) / env -> zSize;
		float r = cur -> getColor().x * colorScale;
		float g = cur -> getColor().y * colorScale;
		float b = cur -> getColor().z * colorScale;
		glColor3f(r,g,b);
		glPushMatrix();
		glTranslatef(position.x, position.y, position.z);
		glutSolidSphere(cur -> getVolume(), 5, 5);
		glPopMatrix();
	}

	/*glBegin(GL_POINTS);

	for(int i = 0; i < env -> numParticles; i++)
	{
		Particle* cur;
		cur = env->particles.getParticle(i);

		position = cur -> getPosition();
		float r = cur -> getColor().x;
		float g = cur -> getColor().y;
		float b = cur -> getColor().z;
		glColor3f(r, g, b);
		glVertex3f(position.x, position.y, position.z);
	}
	glEnd();*/
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

void Draw::displayBackdrop()
{
	glBegin(GL_QUADS); // Start drawing a quad primitive
	glColor3f(0.1f, 0.1f, 0.1f);
	glVertex3f(0.0f, 0.0f, 0.0f); // The bottom left corner
	glVertex3f(env -> xSize, 0.0f, 0.0f); // The bottom right corner
	glVertex3f(env -> xSize, 0.0f, env -> zSize-1); // The top right corner
	glVertex3f(0.0f, 0.0f, env -> zSize-1); // The top left corner

	glEnd();
}
