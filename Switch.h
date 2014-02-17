#ifndef SWITCH_H_
#define SWITCH_H_

#ifdef __APPLE__
#include "/usr/local/Cellar/freeglut/2.8.1/include/GL/glut.h"
#include "/usr/local/Cellar/freeglut/2.8.1/include/GL/freeglut_ext.h"
#include "/usr/local/Cellar/freeglut/2.8.1/include/GL/freeglut_std.h"
#include "/usr/local/Cellar/freeglut/2.8.1/include/GL/freeglut.h"
#else
#include <GL/freeglut.h>  // GLUT, includes glu.h and gl.h
#include <windows.h>
#endif

#include "Physics.h"
#include "Draw.h"
#include <iostream>
#ifdef __APPLE__
#define pixels 720
#else
#define pixels 900
#endif

class Switch{
public:
    
    Switch(float x, float y, int numPs, int argc, char** argv);
    void init(float sizeX, float sizeY, int argc, char** argv);
    static void display();
    static void timer(int id);

};
#endif
