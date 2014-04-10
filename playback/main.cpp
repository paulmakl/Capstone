#include <iostream>
#include <fstream>
#include <string>
#include "reader.h"
#include "Draw.h"

#ifdef __APPLE__
#include "/usr/local/Cellar/freeglut/2.8.1/include/GL/glut.h"
#include "/usr/local/Cellar/freeglut/2.8.1/include/GL/freeglut_ext.h"
#include "/usr/local/Cellar/freeglut/2.8.1/include/GL/freeglut_std.h"
#include "/usr/local/Cellar/freeglut/2.8.1/include/GL/freeglut.h"
#include <OpenGL/glu.h>
#else
#include <GL/freeglut.h>  // GLUT, includes glu.h and gl.h
#include <windows.h>
#endif

#ifdef __APPLE__
#define pixels 720
#define path "/Users/paulmakl/Documents/Capstone/playback/video.txt"
#else
#define pixels 900
#define path "C://Users/Etan/Desktop/video2.txt"
#endif

using namespace std;
fstream myfile;
float frame = 0;
int oldTime = 0;
int curTime = 0;
int curState = 0;
reader x(path);
Draw drawer;

void timer(int id)
{
	glutPostRedisplay();
}

void display()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
	glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer
    
    glPushMatrix();
    
    drawer.displayBackdrop();
    drawer.displayParticles(curState);
    
    curTime = glutGet(GLUT_ELAPSED_TIME);
    
	// Calculate only if the difference is greater than 1 second.
	if(curTime - oldTime > 1000)
	{
		//std::cout << "FPS: " << frame*1000.0f/(curTime - oldTime) << "\n";
        //	char unsigned display[] = { 'F','P','S',':', ' ', '\0'};
        //	glutBitmapString(GLUT_BITMAP_HELVETICA_10, display);
		oldTime = curTime;
		frame = 0;
	}
    
    glPopMatrix();
    
    
	glFlush();
	glutSwapBuffers();
	glutTimerFunc(50, timer, 0);
    curState += 1;
    if(curState >= x.vid.states.size())
    {
        glutLeaveMainLoop();
    }
}

int main(int argc, char** argv)
{
    x.read();
    drawer.init(&x.vid);
    glutInit(&argc, argv); // Initialize GLUT
	//glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    
	glutInitWindowSize(pixels, pixels); // Set the window's initial width & height
	glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
	glutCreateWindow("Video Tiem"); // Create a window with the given title
    
	glutDisplayFunc( display ); // Register display callback handler for window re-paint
    
    glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    
	gluPerspective(85.0, 1.0, 0.001, x.vid.size.x);
	float eyeX, eyeY, eyeZ, targetX, targetY, targetZ, upX, upY, upZ;
    float distance = x.vid.size.x;
    eyeX = distance;//*cos(angle);
    eyeY = 3.0f;//env.ySize/1.3f;
    eyeZ = distance;//*sin(angle);
    targetX = x.vid.size.x/2.0f;
    targetY = x.vid.size.y/2.0f;
    targetZ = x.vid.size.z/2.0f;
    upX = 0.0f;
    upY = 1.0f;
    upZ = 0.0f;
    
    gluLookAt(eyeX, eyeY, eyeZ, targetX, targetY, targetZ, upX, upY, upZ);
    
    
    
    glutMainLoop();
	return 0;
};
