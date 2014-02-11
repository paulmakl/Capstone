#include "Switch.h"

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
    glutInitWindowSize(720, 720); // Set the window's initial width & height
    glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
    glutCreateWindow("Snow Tiem"); // Create a window with the given title
    
    //glutIdleFunc(idle); // Method called when we are idle.
    
    srand(time(NULL)); // Turn this off if you want a random value uniform across all simulations.
    
    env.generateNodes();
    env.generateParticles();
    //env.generateShapes();
    
    glutDisplayFunc( display ); // Register display callback handler for window re-paint
    
    glOrtho(0.0f , env.xSize, 0.0f, env.ySize, 30.0, -10.0);
}

void Switch::timer(int id)
{
	glutPostRedisplay();
}

void Switch::display(void)
{
/*<<<<<<< HEAD
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
    glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer
    
    phys.updatePositions();
    
    glPushMatrix();
    
    draw.displayGrid();
    draw.displayParticles();
    
    glTranslatef(env.xSize/2.0f, env.ySize/2.0f, 0.0f);
    
    glColor3f(0.5f, 0.5f, 0.5f);
    
    glPopMatrix();
    
    glFlush();
    glutSwapBuffers();
    
    glutTimerFunc(50, Switch::timer, 0);
    disps++;
}
=======*/
	//glClearDepth(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
	glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer

	//phys.updateGridForces(); // Reset the grid velocities and extrapolate particles forces to the grid.
	phys.updateParticlePositions();
	phys.updateShapePositions();
	phys.checkEulerianCollisions();

	glPushMatrix();

	draw.displayGrid();
	draw.displayParticles();
	draw.displayShapes();

	glPopMatrix();

	glFlush();
	glutSwapBuffers();
	// TODO: The method specified must be static, but this will require to make a whole lot of stuff static.
	glutTimerFunc(50, timer, 0);
}
//>>>>>>> 19edcd17071ef4e2530151086b0ef76d8c4cc3f7
