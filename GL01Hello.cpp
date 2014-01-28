/*
 * GL01Hello.cpp: Test OpenGL C/C++ Setup
 */

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>  // GLUT, includes glu.h and gl.h
//#include <CL/opencl.h>
#include <windows.h>
#endif

#define xSize 64
#define ySize 64

	class Node
	{
	public:
		int id; // Shoddy code; -1 if non-existant or placeholder.
		float color[4];
		void setRGB(float r, float g, float b)
		{
			color[0] = r;
			color[1] = g;
			color[2] = b;
			color[3] = 1.0f;
		}
		float getColor()
		{
			return color[0];
		}
	};

	class Particle
	{
	public:
		float position[2];
		float velocity[2];
	};

	Node grid[xSize][ySize];

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


		//glFrustrum(-1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 1.0f);
		//glEnable(GL_DEPTH_TEST);
		// Draw a Red 1x1 Square centered at origin
//		glBegin(GL_QUADS); // Each set of 4 vertices form a quad
//		glColor3f(1.0f, 1.0f, 0.0f);
//		glVertex3f(-2.0f, -2.0f, -2.2f);
//		glColor3f(0.0f, 1.0f, 0.0f);
//		glVertex3f( 2.0f, -2.0f, -2.2f);
//		glColor3f(0.0f, 0.0f, 1.0f);
//		glVertex3f( 2.0f,  2.0f, -2.2f);
//		glColor3f(0.0f, 0.0f, 0.0f);
//		glVertex3f(-2.0f,  2.0f, -2.2f);
//		glEnd();

		glBegin(GL_POINTS);

		float xPoint, yPoint;
		for(int x = 0; x < xSize; x++)
		{
			for(int y = 0; y < ySize; y++)
			{
				float r, g, b;
				r = 0.0f;
				g = 0.0f;
				b = 0.0f;
				Node cur = grid[x][y];
				r = cur.getColor();
				glColor3f(r, g, b);
				glVertex3f(x, y, 0);
			}
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

	/*
	 * Main function: GLUT runs as a console application starting at main()
	 */
	int main(int argc, char** argv)
	{
		glutInit(&argc, argv);                 // Initialize GLUT
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
		glutInitWindowSize(900, 900);   // Set the window's initial width & height
		glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
		glutCreateWindow("Snow Tiem"); // Create a window with the given title

		glutDisplayFunc(display); // Register display callback handler for window re-paint
		glutIdleFunc(idle); // Method called when we are idle.

		// Provide a Perspective view of our scene.
		gluPerspective(90.0f, 1.0f, 1.0f, -10.0f);
		gluLookAt (xSize/2, ySize/2, 35.0f, xSize/2, ySize/2, -2.0f, 0.0f, 1.0f, 0.0f);


		int x, y;
		float r, g, b;
		for(x = 0; x < xSize; x++)
		{
			for(y = 0; y < ySize; y+= 2)
			{
				Node a;
				r = 0.7f + rand()%30/100.0f;
				g = 0.7f + rand()%30/100.0f;
				b = 0.7f + rand()%30/100.0f;
				float col[4] = {r, g, b, 1.0f};
				a.setRGB(r, g, b);
				grid[x][y] = a;
			}
		}

		glutMainLoop();           // Enter the infinitely event-processing loop
		return 0;
	}
