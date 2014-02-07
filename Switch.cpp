#include "Switch.h"

<<<<<<< HEAD
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

	// TODO: The method specified must be static, but this will require to make a whole lot of stuff static.
	glutDisplayFunc(Switch::display); // Register display callback handler for window re-paint

	// Provide a Perspective view of our scene.
	//gluPerspective(90.0f, 1.0f, 1.0f, -10.0f);
	//gluLookAt(xSize/2, ySize/2, 35.0f, xSize/2, ySize/2, -200.0f, 0.0f, 1.0f, 0.0f);


	glOrtho(0.0f , xSize, 0.0f, ySize, 30.0, -10.0);
}

void Switch::timer(int id)
{
	glutPostRedisplay();
}

void Switch::display()
{
	//glClearDepth(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
	glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer

	phys.updatePositions();

	glPushMatrix();
	draw.displayGrid();
	draw.displayParticles();
	glTranslatef(xSize/2.0f, ySize/2.0f, 0.0f);
	//glRotatef(degree, 0.0f, 0.0f, 1.0f);
	//degree+= 1.5f;
	glColor3f(0.5f, 0.5f, 0.5f);
	/*for(int i; i < numShapes; i++)
	{

		shapes[i].draw();
	}*/

	//glutWireCube(10.0f);
	glPopMatrix();

	glFlush();
	glutSwapBuffers();
	// TODO: The method specified must be static, but this will require to make a whole lot of stuff static.
	glutTimerFunc(50, Switch::timer, 0);
}
=======
void Switch::init(){
    
}

void Switch::loop(){
    
    
}
>>>>>>> 7c40d12ca73902e6aa832c090e28c900f5c17c32
