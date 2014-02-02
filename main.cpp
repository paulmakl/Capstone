/*
 * main.cpp: Test OpenGL C/C++ Setup
 * Authors: Etan Bard, Paul Makl
 * Version: 1/27/2014
 */

#ifdef __APPLE__
#include "/usr/local/Cellar/freeglut/2.8.1/include/GL/glut.h"
#include "/usr/local/Cellar/freeglut/2.8.1/include/GL/freeglut_ext.h"
#include "/usr/local/Cellar/freeglut/2.8.1/include/GL/freeglut_std.h"
#include "/usr/local/Cellar/freeglut/2.8.1/include/GL/freeglut.h"
#else
#include <GL/freeglut.h>  // GLUT, includes glu.h and gl.h
#include <windows.h>
#endif

#include <time.h>
#include <string>
#include <cmath>

#define xSize 64
#define ySize 64
#define numParticles 10000

struct Vec2
{
	float x, y;
};

struct Vec3
{
	float x, y, z;
};

struct Vec4
{
	float r, g, b, a;
};

class Node
{
public:
	Vec4 color;
	Vec2 force;

	void setForce(float x, float y)
	{
		force.x = x;
		force.y = y;
	}

	Vec2 getForce(float x, float y)
	{
		return force;
	}

	void setRGBA(float r, float g, float b, float a)
	{
		color.r = r;
		color.g = g;
		color.b = b;
		color.a = 1.0f;
	}

	Vec4 getRGBA()
	{
		return color;
	}
};

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

Node grid[xSize][ySize];
Particle particles[numParticles];

void timer(int id)
{
	glutPostRedisplay();
}

void displayGrid()
{
	glPointSize(3.0);
	glBegin(GL_POINTS);
	Vec4 color;
	for(int x = 0; x < xSize; x++)
	{
		for(int y = 0; y < ySize; y++)
		{

			Node cur = grid[x][y];
			color = cur.getRGBA();
			glColor3f(color.r, color.g, color.b);
			glVertex3f(x, y, 0);
		}
	}
	glEnd();
}

void displayParticles()
{
	glPointSize(1.0);
	glBegin(GL_POINTS);

	Vec2 position, velocity;

	glColor3f(1.0f, 1.0f, 1.0f);
	for(int i = 0; i < numParticles; i++)
	{
		Particle* cur;
		cur = &particles[i];
		position = cur -> getPosition();
		velocity = cur -> getVelocity();

		int lowX = floor(position.x);
		int highX = ceil(position.x);
		int lowY = floor(position.y);
		int highY = ceil(position.y);

		Vec2 downLeftForce = grid[lowX][lowY].force;
		Vec2 downRightForce = grid[highX][lowY].force;
		Vec2 upLeftForce = grid[lowX][highY].force;
		Vec2 upRightForce = grid[highX][highY].force;

		//float xOffset = position.x - lowX;
		//float yOffset = position.y - lowY;

		Vec2 force;
		// TODO: replace
		force.x = downLeftForce.x + downRightForce.x + upLeftForce.x + upRightForce.x;
		force.y = downLeftForce.y + downRightForce.y + upLeftForce.y + upRightForce.y;
		force.x /= 4;
		force.y /= 4;

		velocity = force;

		if(position.x + velocity.x <= 0 || position.x + velocity.x >= xSize)
			velocity.x = -velocity.x;
		if(position.y + velocity.y <= 0 || position.y  + velocity.y >= ySize)
			velocity.y = -velocity.y;

		cur -> setPosition(position.x + velocity.x, position.y + velocity.y);
		cur -> setVelocity(velocity.x, velocity.y);

		glVertex3f(position.x, position.y, 0);
	}
	glEnd();
}

/* Handler for window-repaint event. Call back when the window first appears and
    whenever the window needs to be re-painted. */
static void display()
{
	//glClearDepth(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
	glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer

	displayGrid();
	displayParticles();

	glFlush();  // Render now
	glutSwapBuffers();
	glutTimerFunc(33, timer, 0);
}

/*
 * Call to redraw the frame when idle.
 */
static void idle()
{
	glutPostRedisplay();
}

static void generateParticles()
{
	float xVelo, yVelo, xPos, yPos;
	for(int i = 0; i < numParticles; i++)
	{

		Particle a;
		xPos = (float)(rand()%6400) / 100.0f;
		yPos = (float)(rand()%6400) / 100.0f;
		a.setPosition(xPos, yPos);

		xVelo = (rand()%10)/1000.0f - 0.0055f;
		yVelo = (rand()%10)/1000.0f - 0.0055f;
		a.setVelocity(xVelo, yVelo);
		particles[i] = a;
	}
}

static void generateNodes()
{
	int x, y;
	float r, g, b;
	for(x = 0; x < xSize; x++)
	{
		for(y = 0; y < ySize; y+= 2)
		{
			Node a;
			r = 0.2f + rand()%30/100.0f;
			g = 0.2f + rand()%30/100.0f;
			b = 0.2f + rand()%30/100.0f;
			a.setRGBA(r, g, b, 1.0f);
			a.setForce(rand()%30/10000.0f, rand()%30/10000.0f);
			grid[x][y] = a;
		}
	}
}

/*
 * Main function: GLUT runs as a console application starting at main()
 */
int main(int argc, char** argv)
{
	glutInit(&argc, argv); // Initialize GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(1600, 900); // Set the window's initial width & height
	glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
	glutCreateWindow("Snow Tiem"); // Create a window with the given title

	glutDisplayFunc(display); // Register display callback handler for window re-paint
	//glutIdleFunc(idle); // Method called when we are idle.

	// Provide a Perspective view of our scene.
	//gluPerspective(90.0f, 1.0f, 1.0f, -10.0f);
	//gluLookAt(xSize/2, ySize/2, 35.0f, xSize/2, ySize/2, -200.0f, 0.0f, 1.0f, 0.0f);

	glOrtho(0.0f , xSize, 0.0f, ySize, 30.0, -10.0);

	generateNodes();

	generateParticles();

	glutMainLoop();           // Enter the infinitely event-processing loop
	return 0;
}
