/*
 * GL01Hello.cpp: Test OpenGL C/C++ Setup
 */
//#include <windows.h>  // For MS Windows
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>  // GLUT, includes glu.h and gl.h
#endif

/* Handler for window-repaint event. Call back when the window first appears and
   whenever the window needs to be re-painted. */
void display()
{
	//glClearDepth(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
	glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer

	//glFrustrum(-1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 1.0f);
	//glEnable(GL_DEPTH_TEST);
	// Draw a Red 1x1 Square centered at origin
	glBegin(GL_QUADS);              // Each set of 4 vertices form a quad
		glRotatef(45.0f, 1.0f, 1.0f, 1.0f);
		glColor3f(1.0f, 0.0f, 0.0f); // Red
		glVertex2f(-0.5f, -0.5f);    // x, y
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex2f( 0.5f, -0.5f);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex2f( 0.5f,  0.5f);
		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex2f(-0.5f,  0.5f);
	glEnd();

	glBegin(GL_POINTS);
		glColor3f(0.0f, 0.5f, 0.5f);
		for(float x = -1.0f; x <= 1.0f; x+= 0.01f)
		{
			for(float y = -1.0f; y <= 1.0f; y+= 0.01f)
			{
				glVertex2f(x, y);
			}
		}
	glEnd();

	glFlush();  // Render now
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {
	glutInit(&argc, argv);                 // Initialize GLUT
	glutInitWindowSize(900, 900);   // Set the window's initial width & height
	glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
	glutCreateWindow("Snow Tiem"); // Create a window with the given title
	glutDisplayFunc(display); // Register display callback handler for window re-paint

	glutMainLoop();           // Enter the infinitely event-processing loop
	return 0;
}
