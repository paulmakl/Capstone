
#include "GLFuncs.h"

void GLFuncs::init(int argc, char **argv)
{
    glutInit(&argc, argv); // Initialize GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(pixels, pixels); // Set the window's initial width & height
	glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
	glutCreateWindow("Snow Tiem"); // Create a window with the given title
    
	glutDisplayFunc(GLFuncs::display); // Register display callback handler for window re-paint
	//glutIdleFunc(idle); // Method called when we are idle.
    
	for(int i = 0; i < numShapes; i++)
	{
		Cube a;
		Vec3 location;
		location.x = 5.0f;
		location.y = 5.0f;
		location.z = 0.0f;
		a.setVariables(5, location);
		shapes[i] = a;
	}

	// Provide a Perspective view of our scene.
	//gluPerspective(90.0f, 1.0f, 1.0f, -10.0f);
	//gluLookAt(xSize/2, ySize/2, 35.0f, xSize/2, ySize/2, -200.0f, 0.0f, 1.0f, 0.0f);
    
	glOrtho(0.0f , xSize, 0.0f, ySize, 30.0, -10.0);
}

void GLFuncs::timer(int id)
{
	glutPostRedisplay();
}

void GLFuncs::displayGrid()
{
	glPointSize(1.0);
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

Vec2 GLFuncs::interpolate(Vec2 a, Vec2 b, float offset)
{
	Vec2 ret;
	ret.x = offset*a.x + (1-offset)*b.x;
	ret.y = offset*a.y + (1-offset)*b.y;
	return ret;
}

void GLFuncs::displayParticles()
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
        
		float xOffset = highX - position.x;
		float yOffset = highY - position.y;
        
		Vec2 r1 = interpolate(downLeftForce, downRightForce, xOffset);
		Vec2 r2 = interpolate(upLeftForce, upRightForce, xOffset);
		velocity = interpolate(r1, r2, yOffset);
        
		if(position.x + velocity.x <= 0 || position.x + velocity.x >= xSize)
			velocity.x = -velocity.x;
		if(position.y + velocity.y <= 0 || position.y  + velocity.y >= ySize)
			velocity.y = -velocity.y;
        
		cur -> setPosition(position.x + velocity.x, position.y + velocity.y);
		cur -> setVelocity((velocity.x + position.x)/2.0f, (velocity.y + position.y)/2.0f);
        
		glVertex3f(position.x, position.y, 0);
	}
	glEnd();
}

/* Handler for window-repaint event. Call back when the window first appears and
 whenever the window needs to be re-painted. */
void GLFuncs::display()
{
	//glClearDepth(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
	glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer
    
	glPushMatrix();
	displayGrid();
	displayParticles();
	glTranslatef(xSize/2.0f, ySize/2.0f, 0.0f);
	//glRotatef(degree, 0.0f, 0.0f, 1.0f);
	//degree+= 1.5f;
	glColor3f(0.5f, 0.5f, 0.5f);
	for(int i; i < numShapes; i++)
	{

		shapes[i].draw();
	}

	//glutWireCube(10.0f);
	glPopMatrix();
    
	glFlush();
	glutSwapBuffers();
	glutTimerFunc(50, timer, 0);
}

/*
 * Call to redraw the frame when idle.
 */
void GLFuncs::idle()
{
	glutPostRedisplay();
}

void GLFuncs::generateParticles()
{
	float xVelo, yVelo, xPos, yPos;
	for(int i = 0; i < numParticles; i++)
	{
        
		Particle a;
		xPos = (float)(rand()%(xSize*100)) / 100.0f;
		yPos = (float)(rand()%(ySize*100)) / 100.0f;
		a.setPosition(xPos, yPos);
        
		xVelo = (rand()%10)/1000.0f - 0.0055f;
		yVelo = (rand()%10)/1000.0f - 0.0055f;
		a.setVelocity(xVelo, yVelo);
		particles[i] = a;
	}
}

void GLFuncs::generateNodes()
{
	int x, y;
	float r, g, b;
	float forceX, forceY;
	forceX = 0.064;
	for(x = 0; x < xSize; x++)
	{
		forceY = 0.0f;
		for(y = 0; y < ySize; y++)
		{
			Node a;
			r = 0.2f + rand()%30/100.0f;
			g = 0.2f + rand()%30/100.0f;
			b = 0.2f + rand()%30/100.0f;
			a.setRGBA(r, g, b, 1.0f);
			a.setForce(forceX + rand()%100/1000.0f - 0.055f, forceY + rand()%100/1000.0f - 0.055f); //, rand()%100/1000.0f - 0.055f);
			grid[x][y] = a;
			forceY += 0.002f;
		}
		forceX += 0.002f;
	}


}

void drawCube(float length, Vec3 location)
	{
		glutWireCube(10.0f);
	}

	//void drawSphere(float radius, Vec3 location);
