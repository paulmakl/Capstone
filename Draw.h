#ifndef DRAW_H_
#define DRAW_H_

<<<<<<< HEAD
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

#include "Environment.h"

class Draw{
public:
    Environment* env;
    
    //Draw(Environment* envPointer);
    void temp(Environment* envPointer);
    void displayGrid();
    void displayParticles();
    void displayShapes();
};

#endif
=======
#include "Environment.h"

class Draw{
    Environment* env;
    
    Draw(Environment* envPointer);
};

#endif
>>>>>>> 7c40d12ca73902e6aa832c090e28c900f5c17c32
