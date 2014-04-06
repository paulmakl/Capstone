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

/*#define xWidth 64
#define yWidth 64
#define zWidth 64 // Keep these the same for now!
#define Particles 1000
*/

#include "Switch.h"
#include "Randy.h"
#include "vectors.h"
#include <iostream>

/**
 * The main function will initialize a switch instance, then proceed to initiate the FreeGLUT loop.
 */
int main(int argc, char** argv)
{
	int xa = 64;
	int ya = 64;
	int za = 64;
	int p = 8000;
    Switch x(xa, ya, za, p, argc, argv);
   	glutMainLoop();

	return 0;
};
