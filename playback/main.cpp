#include <iostream>
#include <fstream>
#include <string>
#include "reader.h"
#include "Draw.h"
#include "camera.h"

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
#define path "C://Users/Etan/Desktop/video.txt"
#endif

using namespace std;
fstream myfile;
float frame = 0;
int oldTime = 0;
int curTime = 0;
int curState = 0;
reader x(path);
camera cam;
Draw drawer;
float eyeX, eyeY, eyeZ, targetX, targetY, targetZ, upX, upY, upZ;
float distance;
float angle;

float fovy = 85;
float aspect = 1.0;
float zfar;

void timer(int id)
{
	glutPostRedisplay();
}

void display(){
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
	glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer
    //gluLookAt(cam.eyeX, cam.eyeY, cam.eyeZ, cam.targetX, cam.targetY, cam.targetZ, cam.upX, cam.upY, cam.upZ);
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
    
    if(curState < x.vid.states.size() - 1){
        curState += 1;
    }else{
        //glutLeaveMainLoop();
    }
}

void keyboard(unsigned char key, int x, int y)
{
    
    switch(key)
	{
            // Backspace
        case 8 :
            std::cout << "Pressed Backspace" << std::endl;
            curState = 0;
            break;
        case 113 :
            cout << "q" << endl;
            glTranslated(1, 0, 0);
            break;
        case 97 :
            cout << "a" << endl;
            glTranslated(-1, 0, 0);
            break;
        case 119 :
            cout << "w" << endl;
            glTranslated(0, 1, 0);
            break;
        case 115 :
            cout << "s" << endl;
            glTranslated(0, -1, 0);
            break;
        case 101 :
            cout << "e" << endl;
            glTranslated(0, 0, 1);
            break;
        case 100 :
            cout << "d" << endl;
            glTranslated(0, 0, -1);
            break;
        case 114 :
            cout << "r" << endl;
            glRotatef(1.0,0.0,1.0,0.0);
            break;
        case 102 :
            cout << "f" << endl;
            glRotatef(-1.0,0.0,1.0,0.0);
            break;
            // Delete
        case 127 :
            cout << "Pressed Delete" << endl;
            break;
        default :
            break;
	}
    int mod = glutGetModifiers();
    switch(mod)
	{
        case GLUT_ACTIVE_CTRL :
            cout << "Ctrl Held" << endl; break;
        case GLUT_ACTIVE_SHIFT :
            cout << "Shift Held" << endl; break;
        case GLUT_ACTIVE_ALT :
            cout << "Alt Held" << endl; break;
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
    glutKeyboardFunc(keyboard);
    
    glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    
	//gluPerspective(85.0, 1.0, 0.001, x.vid.size.x);
    gluPerspective(fovy, aspect, 0.001, x.vid.size.x);
	float eyeX, eyeY, eyeZ, targetX, targetY, targetZ, upX, upY, upZ;
    float distance = x.vid.size.x;
    eyeX = distance;//*cos(angle);
    eyeY = 5;//env.ySize/1.3f;
    eyeZ = distance;//*sin(angle);
    targetX = x.vid.size.x/2.0f;
    targetY = x.vid.size.y/2.0f;
    targetZ = x.vid.size.z/2.0f;
    upX = 0.0f;
    upY = 1.0f;
    upZ = 0.0f;
    cam.init(eyeX, eyeY, eyeZ, targetX, targetY, targetZ, upX, upY, upZ);
    gluLookAt(eyeX, eyeY, eyeZ, targetX, targetY, targetZ, upX, upY, upZ);
    /*glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluLookAt(eyeX, eyeY, eyeZ, targetX, targetY, targetZ, upX, upY, upZ);*/
    glutMainLoop();
	return 0;
};
