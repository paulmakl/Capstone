#include "Switch.h"
#include <math.h>
#include <iostream>
#include <sstream>

Environment env;
Physics phys;
Draw draw;
int disps = 0;
int frame, oldTime, curTime;
std::ofstream myfile;
float angle = 0;
bool ignoreRepeats = false;
//int index = 0;
int particles = 0;
int releasedParticles = 0;
bool snowballFlag = false; // Becomes true when we release a snowball.

using namespace std;


Switch::Switch(float xWidth, float yWidth, float zWidth, int numPs, int argc, char** argv)
{
	particles = numPs;

	env.init(xWidth, yWidth, zWidth, numPs);

	phys.init(&env);
	draw.init(&env);

	glutInit(&argc, argv); // Initialize GLUT
	//glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

	glutInitWindowSize(pixels, pixels); // Set the window's initial width & height
	glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
	glutCreateWindow("Snow Tiem"); // Create a window with the given title

	glutDisplayFunc( display ); // Register display callback handler for window re-paint
	//glutKeyboardFunc(keyboard);
	frame = 0;
	oldTime = 0;
	curTime = 0;


	//glOrtho(-0.1f , env.xSize - 0.9f, -0.1f, env.ySize - 0.9f, 30.0, -10.0);
	//myfile.open("/Users/paulmakl/Documents/Capstone/video.txt");

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	gluPerspective(85.0, 1.0, 0.001, env.xSize*2);
	float eyeX, eyeY, eyeZ, targetX, targetY, targetZ, upX, upY, upZ;
	float distance = env.xSize;
	angle = 0.0f;
	eyeX = env.xSize/2.0f;//*cows(angle);
	eyeY = env.ySize/3.0f;//env.ySize/1.3f;
	eyeZ = -5.0f;//*sin(angle);
	targetX = env.xSize/2.0f;
	targetY = 3.0f;
	targetZ = env.zSize/2.0f;
	upX = 0.0f;
	upY = 1.0f;
	upZ = 0.0f;

	gluLookAt(eyeX, eyeY, eyeZ, targetX, targetY, targetZ, upX, upY, upZ);

	//glOrtho(-0.1f , env.xSize - 0.9f, -0.1f, env.ySize - 0.1f, env.zSize, -0.1f);
	myfile.open(path);
	myfile << "$size\n" << xWidth << "," << yWidth << "," << zWidth << "," << numPs << "\n";

	//float light_position[] = { 0, 0, 1, 0.0f };
	//float light_ambient[] = {1.0f, 1.0f, 1.0f, 0.0f };
	//float light_diffuse[] = { 1.0f, 1.0f, 1.0f, 0.0f };

	//glLightfv(GL_LIGHT0, GL_SPECULAR, light_ambient);
	//glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);

	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);
	//glShadeModel(GL_SMOOTH);
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

	//float light_position[] = { env.xSize/2, env.ySize, env.zSize/2, 0.0f };
	//glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	//float mat_ambient[] = { 0.1f, 0.1f, 0.1f, 1.0f };
	//float mat_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	//glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);

	/*gluPerspective(85.0, 1.0, 0.0, env.xSize);
	float eyeX, eyeY, eyeZ, targetX, targetY, targetZ, upX, upY, upZ;
	float distance = env.xSize;
	angle = 50.0f;
	eyeX = distance*cos(0.01f);
	eyeY = env.ySize/2.0f;
	eyeZ = distance*sin(0.01f);
	targetX = env.xSize/2.0f;
	targetY = env.ySize/2.0f;
	targetZ = env.zSize/2.0f;
	upX = 0.0f;
	upY = 1.0f;
	upZ = 0.0f;

	gluLookAt(eyeX, eyeY, eyeZ, targetX, targetY, targetZ, upX, upY, upZ);*/


	// Reset all nodes to have clean forces.
	phys.resetNodes();

	// Sorts all particles to group them together by boxID.
	env.sortParticles();

	// Extrapolate particles forces to the grid.
	//phys.gravity();
	phys.updateGridForces();

	// Interpolate forces from the grid to the particles
	phys.updateParticleVelocities();
	//phys.checkParticleCollisions();
	phys.updateParticlePositions();
	//phys.updateShapePositions();
	phys.checkEulerianCollisions();

	glPushMatrix();

	draw.displayBackdrop();
	draw.displayParticles();
	//draw.displayGrid();
	//draw.displayShapes();

	if(releasedParticles < particles)
	{
		env.releaseParticles(50);
		releasedParticles += 50;
	}
	else if(!snowballFlag)
	{
		Vec3 center;
		center.x = 32.0f;
		center.y = 1.5f;
		center.z = 32.0f;
		//env.particles.createCOG(center, 2.0f, 10000);
		//env.injectParticles(10000);
		snowballFlag = true;
	}

	frame++;
	curTime = glutGet(GLUT_ELAPSED_TIME);

	// Calculate only if the difference is greater than 1 second.
	if(curTime - oldTime > 1000)
	{
		std::cout << "FPS: " << frame*1000.0f/(curTime - oldTime) << "\n";
		//	char unsigned display[] = { 'F','P','S',':', ' ', '\0'};
		//	glutBitmapString(GLUT_BITMAP_HELVETICA_10, display);
		oldTime = curTime;
		frame = 0;
	}

	glPopMatrix();

	glFlush();
	glutSwapBuffers();
	glutTimerFunc(50, timer, 0);
	//std::cout << disps << " ";

	/*if (disps > FRAME_LIMIT)
	{
        glutLeaveMainLoop();
    }
    std::cout << disps << "\n";
    myfile << "$" << disps << "," << env.numParticles << "\n" ;
    for (int i = 0; i < env.particles.particles.size(); i++)
    {
        myfile
               << env.particles.particles[i].getPosition().x << ","
               << env.particles.particles[i].getPosition().y << ","
               << env.particles.particles[i].getPosition().z;
        if (i != env.particles.particles.size() - 1)
        {
            myfile << "\n";
        }
    }*/
    disps++;
    myfile << "\n";
}
