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

<<<<<<< HEAD
#include "Switch.h"
=======
/*#include <time.h>
#include <string>
#include <cmath>
#include "Constants.h"
#include "vectors.h"
#include "Node.h"
#include "Particle.h"*/
#include "GLFuncs.h"
>>>>>>> 7c40d12ca73902e6aa832c090e28c900f5c17c32

/*
 * Main function: GLUT runs as a console application starting at main()
 */
int main(int argc, char** argv)
{
   	Switch runtime;
   	runtime.init(argc, argv);
   	glutMainLoop();
	return 0;
}
