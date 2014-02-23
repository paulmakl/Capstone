/*
 * main.cpp: Test OpenGL C/C++ Setup
 * Authors: Etan Bard, Paul Makl
 * Version: 2/2/2014
 */

#ifdef __APPLE__
#include "/usr/local/Cellar/freeglut/2.8.1/include/GL/glut.h"
#include "/usr/local/Cellar/freeglut/2.8.1/include/GL/freeglut_ext.h"
#include "/usr/local/Cellar/freeglut/2.8.1/include/GL/freeglut_std.h"
#include "/usr/local/Cellar/freeglut/2.8.1/include/GL/freeglut.h"
#else
#include <GL/freeglut.h>  // GLUT, includes glu.h and gl.h
#include <windows.h>
#endif

#define xWidth 30
#define yWidth 30 // For now, keep xSize and ySize the same!
#define Particles 10000
#include "Switch.h"
#include "Randy.h"
#include <iostream>
/*
 * Main function
 */
int main(int argc, char** argv)
{
    Switch x(xWidth, yWidth, Particles, argc, argv);
   	glutMainLoop();
	return 0;
};
