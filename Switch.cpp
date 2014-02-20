#include "Switch.h"
#include <iostream>
Environment env;
Physics phys;
Draw draw;
int disps = 0;

Switch::Switch(float x, float y, int numPs, int argc, char** argv)
{
    
    env.init(x, y, numPs);
    
    phys.init(&env);
    draw.init(&env);
    
    glutInit(&argc, argv); // Initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(pixels, pixels); // Set the window's initial width & height
    glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
    glutCreateWindow("Snow Tiem"); // Create a window with the given title
    
    glutDisplayFunc( display ); // Register display callback handler for window re-paint
    
    glOrtho(-1.0f , env.xSize, -1.0f, env.ySize, 30.0, -10.0);
}

void Switch::timer(int id)
{
	glutPostRedisplay();
}

void Switch::display(void)
{
	//glClearDepth(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
	glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer

    phys.resetNodes();
    env.sortParticles();
	phys.updateGridForces(); // Reset the grid velocities and extrapolate particles forces to the grid.
	phys.updateParticlePositions();
	phys.updateShapePositions();
	//phys.checkEulerianCollisions();

	glPushMatrix();

	draw.displayGrid();
	draw.displayParticles();
	draw.displayShapes();

	glPopMatrix();

	glFlush();
	glutSwapBuffers();
	glutTimerFunc(50, timer, 0);
    //std::cout << disps << " ";
    //disps++;
}
