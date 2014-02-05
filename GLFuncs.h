#ifndef GLFUNCS_H_
#define GLFUNCS_H_

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

#include "Constants.h"
#include "Particle.h"
#include "Node.h"
#include <math.h>
#include <time.h>
#include "Shape.h"
#include "Cube.h"
#include "Sphere.h"
#pragma once

class GLFuncs{
    
public:
    static void init(int argc, char** argv);
    
    static void displayGrid();
    
    static void displayParticles();
    
    /*
     * Call to redraw the frame when idle.
     */
    static void idle();
    
    static Vec2 interpolate(Vec2 a, Vec2 b, float offset);
    
    static void timer(int id);
    
    /* Handler for window-repaint event. Call back when the window first appears and
     whenever the window needs to be re-painted. */
    static void display();
    

    
    static void generateParticles();
    
    static void generateNodes();
    
    static void drawCube(float length, Vec3 location);
    static void drawSphere(float radius, Vec3 location);
    
};

#endif /* GLFUNCTIONS_H_ */
