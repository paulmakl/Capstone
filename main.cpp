/*
 * main.cpp: Test OpenGL C/C++ Setup
 * Authors: Etan Bard, Paul Makl
 * Version: 1/27/2014
 */

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>  // GLUT, includes glu.h and gl.h
#include <windows.h>
#endif

#include <time.h>

#define xSize 64
#define ySize 64
#define numParticles 2000

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

void setGrid(Node* newGrid[xSize][ySize])
{
	int x, y;
	for(x = 0; x < xSize; x++)
	{
		for(y = 0; y < ySize; y++)
		{
			grid[x][y] = *newGrid[x][y];
		}
	}
}

/* Handler for window-repaint event. Call back when the window first appears and
    whenever the window needs to be re-painted. */
static void display()
{
	//glClearDepth(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
	glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer

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

	glBegin(GL_POINTS);

	Vec2 position, velocity;
	for(int i = 0; i < numParticles; i++)
	{
		float r, g, b;
		r = 1.0f;
		g = 1.0f;
		b = 1.0f;
		Particle* cur = &particles[i];
		position = cur -> getPosition();
		velocity = cur -> getVelocity();
		if(position.x + velocity.x <= 0 || position.x + velocity.x >= xSize)
			velocity.x = -velocity.x*2;
		if(position.y + velocity.y <= 0 || position.y  + velocity.y >= ySize)
			velocity.y = -velocity.y*2;

		cur -> setPosition(position.x + velocity.x, position.y + velocity.y);

		glColor3f(r, g, b);
		glVertex3f(position.x, position.y, 0);
	}
	glEnd();


	glVertex3f(32.0f, 32.0f, 0);
	//glutSolidTeapot(2.0);

	glFlush();  // Render now
	glutSwapBuffers();
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

/*
 * Main function: GLUT runs as a console application starting at main()
 */
int main(int argc, char** argv)
{
	glutInit(&argc, argv); // Initialize GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(900, 900); // Set the window's initial width & height
	glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
	glutCreateWindow("Snow Tiem"); // Create a window with the given title

	glutDisplayFunc(display); // Register display callback handler for window re-paint
	glutIdleFunc(idle); // Method called when we are idle.

	// Provide a Perspective view of our scene.
	gluPerspective(90.0f, 1.0f, 1.0f, -10.0f);
	gluLookAt (xSize/2, ySize/2, 35.0f, xSize/2, ySize/2, -200.0f, 0.0f, 1.0f, 0.0f);

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
			a.setForce(0.0f, -0.001f);
			grid[x][y] = a;
		}
	}

	generateParticles();

	glutMainLoop();           // Enter the infinitely event-processing loop
	return 0;
}
