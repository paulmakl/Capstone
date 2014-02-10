#include "Switch.h"

#include "Physics.h"
#include "Draw.h"

	Environment env;
    Physics phys;
    Draw draw;

    void init(int argc, char **argv);
    void timer(int id);
    void display();

void Switch::init(int argc, char **argv)
{
	phys.temp(&env);
	draw.temp(&env);

	glutInit(&argc, argv); // Initialize GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(pixels, pixels); // Set the window's initial width & height
	glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
	glutCreateWindow("Snow Tiem"); // Create a window with the given title

	//glutIdleFunc(idle); // Method called when we are idle.

	//srand(time(NULL)); // Turn this off if you want a random value uniform across all simulations.

	/*for(int i = 0; i < numShapes; i++)
		{
			Cube a;
			Vec3 location;
			location.x = 5.0f;
			location.y = 5.0f;
			location.z = 0.0f;
			a.setVariables(5, location);
			shapes[i] = a;
		}*/


	env.generateNodes();
	env.generateParticles();
	env.generateShapes();

	// TODO: The method specified must be static, but this will require to make a whole lot of stuff static.
	glutDisplayFunc(display); // Register display callback handler for window re-paint

	// Provide a Perspective view of our scene.
	//gluPerspective(90.0f, 1.0f, 1.0f, -10.0f);
	//gluLookAt(xSize/2, ySize/2, 35.0f, xSize/2, ySize/2, -200.0f, 0.0f, 1.0f, 0.0f);


	glOrtho(0.0f , xSize, 0.0f, ySize, 30.0, -10.0);
}

void timer(int id)
{
	glutPostRedisplay();
}

void display()
{
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
