#include "Node.h"
#include "Particle.h"
#pragma once
#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#ifdef __APPLE__
#define pixels 720
#else
#define pixels 900
#endif

#define xSize 64
#define ySize 64 // For now, keep xSize and ySize the same!
#define numParticles 100000

Node grid[xSize][ySize];
Particle particles[numParticles];
float degree = 0;

const GLfloat quadVertices[] = {
		-1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f,-1.0f, 0.0f,
		-1.0f,-1.0f, 0.0f
};

#endif /* CONSTANTS_H_ */
