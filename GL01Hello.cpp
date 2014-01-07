/*
 * GL01Hello.cpp: Test OpenGL C/C++ Setup
 */

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>  // GLUT, includes glu.h and gl.h
#include <CL/opencl.h>
#include <windows.h>
#endif

struct Particle
{
public:
	int id; // Shoddy code; -1 if non-existant or placeholder.
	float color[4];
};
class GL01Hello
{
public:
	static Particle* grid[][240][240];

	void setGrid(Particle* newGrid[240][240][240])
	{
		int x, y, z;
		for(x = 0; x < 240; x++)
		{
			for(y = 0; y < 240; y++)
			{
				for(z = 0; z < 240; z++)
				{
					grid[x][y][z] = newGrid[x][y][z];
				}
			}
		}
	}

	/* Primitive gravity method that will place the particles lower in the grid if the spot is free and exists. */
	void applyGravity(Particle* grid[240][240][240], int x, int y, int z)
	{
		if(y != 0 && grid[x][y][z] == NULL)
		{
			if(grid[x][y-1][z] == NULL)
			{
				// Move particle down 1.
				grid[x][y-1][z] = grid[x][y][z];
				grid[x][y][z] = NULL;
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


		//glFrustrum(-1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 1.0f);
		//glEnable(GL_DEPTH_TEST);
		// Draw a Red 1x1 Square centered at origin
		glBegin(GL_QUADS); // Each set of 4 vertices form a quad
		glColor3f(1.0f, 1.0f, 0.0f);
		glVertex3f(-2.0f, -2.0f, -2.2f);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f( 2.0f, -2.0f, -2.2f);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f( 2.0f,  2.0f, -2.2f);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-2.0f,  2.0f, -2.2f);
		glEnd();

		glBegin(GL_POINTS); // TODO: Hard coded for 1,728,000 particles (1.728 million).
		for(float x = -1.5f; x <= 1.5f; x+= 0.0125f)
		{
			for(float y = -1.5f; y <= 1.5f; y+= 0.0125f)
			{
				for(float z = -1.5f; z <= 1.5f; z+= 0.0125f)
				{
					float r, g, b;
					r = 0.7f + rand()%30/100.0f;
					g = 0.7f + rand()%30/100.0f;
					b = 0.7f + rand()%30/100.0f;
					glColor3f(r, g, b);
					glVertex3f(x, y, z);
				}
			}
		}
		glEnd();

		glFlush();  // Render now
		glutSwapBuffers();
	}
	static void idle()
	{
		glutPostRedisplay();
	}
};

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv)
{
	glutInit(&argc, argv);                 // Initialize GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(900, 900);   // Set the window's initial width & height
	glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
	glutCreateWindow("Snow Tiem"); // Create a window with the given title

	glutDisplayFunc(GL01Hello::display); // Register display callback handler for window re-paint
	glutIdleFunc(GL01Hello::idle); // Method called when we are idle.

	// Provide a Perspective view of our scene.
	gluPerspective(90.0f, 1.0f, 1.0f, -10.0f);
	gluLookAt (0.0f, 2.0f, 5.0f, 0.0f, 0.0f, -2.0f, 0.0f, 1.0f, 0.0f);


	/*int x, y, z;
	for(x = 0; x < 240; x++)
	{
		for(y = 0; y < 240; y++)
		{
			for(z = 0; z < 240; z++)
			{
				Particle a;
				//GL10Hello::grid[x][y][z] = &a;
			}
		}
	}*/

	glutMainLoop();           // Enter the infinitely event-processing loop
	return 0;
}

