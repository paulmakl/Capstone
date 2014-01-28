/*
 * main.cpp: Test OpenGL C/C++ Setup
 * Authors: Etan Bard, Paul Makl
 * Version: 1/27/2014
 */

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>  // GLUT, includes glu.h and gl.h
#include <windows.h>
#endif

#include <time.h>

#define xSize 64
#define ySize 64
#define numParticles 2000

class Node
{
public:
	float color[4];

	void setRGB(float r, float g, float b)
	{
		color[0] = r;
		color[1] = g;
		color[2] = b;
		color[3] = 1.0f;
	}

	float getR()
	{
		return color[0];
	}
	float getG()
	{
		return color[1];
	}
	float getB()
	{
		return color[2];
	}
};

class Particle
{
public:
	float position[2];
	float velocity[2];

	void setPosition(float x, float y)
	{
		position[0] = x;
		position[1] = y;
	}
	void setVelocity(float x, float y)
	{
		velocity[0] = x;
		velocity[1] = y;
	}
	float getVelocityX()
	{
		return velocity[0];
	}
	float getVelocityY()
	{
		return velocity[1];
	}
	float getPositionX()
	{
		return position[0];
	}
	float getPositionY()
	{
		return position[1];
	}
};

Node grid[xSize][ySize];
Particle particles[2000];
float asdf = 2000;

void setGrid(Node* newGrid[240][240])
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
	for(int x = 0; x < xSize; x++)
	{
		for(int y = 0; y < ySize; y++)
		{
			float r, g, b;
			r = 0.0f;
			g = 0.0f;
			b = 0.0f;
			Node cur = grid[x][y];
			r = cur.getR();
			g = cur.getG();
			b = cur.getB();
			glColor3f(r, g, b);
			glVertex3f(x, y, 0);
		}
	}
	glEnd();

	glBegin(GL_POINTS);

	float xPoint, yPoint, xVelo, yVelo;
	for(int i = 0; i < asdf; i++)
	{
		float r, g, b;
		r = 1.0f;
		g = 1.0f;
		b = 1.0f;
		Particle* cur = &particles[i];
		xPoint = cur -> getPositionX();
		yPoint = cur -> getPositionY();
		xVelo = cur -> getVelocityX();
		yVelo = cur -> getVelocityY();
		if(xPoint + xVelo <= 0 || xPoint + xVelo >= xSize)
			xVelo = -xVelo;
		if(yPoint + yVelo <= 0 || yPoint  + yVelo>= ySize)
			yVelo = -yVelo;

		cur -> setPosition(xPoint + xVelo, yPoint + yVelo);
		glColor3f(r, g, b);
		glVertex3f(xPoint, yPoint, 0);
	}
	glEnd();

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
			float col[4] = {r, g, b, 1.0f};
			a.setRGB(r, g, b);
			grid[x][y] = a;
		}
	}

	generateParticles();

	glutMainLoop();           // Enter the infinitely event-processing loop
	return 0;
}
