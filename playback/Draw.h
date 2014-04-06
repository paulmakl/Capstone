#ifndef DRAW_H_
#define DRAW_H_

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

#include "video.h"

class Draw{
public:
    
    video * vid;
    void init(video* vid);
    
    void displayGrid();
    void displayParticles(int state);
    void displayShapes();
    void displayBackdrop();
};

#endif
