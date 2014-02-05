#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#include "Shape.h"
//#include "Node.h"
#include "Particle.h"

#ifdef __APPLE__
#define pixels 720
#else
#define pixels 900
#endif

#define xSize 64
#define ySize 64 // For now, keep xSize and ySize the same!
#define numParticles 100000
#define numShapes 1

static Node grid[xSize][ySize];
static Particle particles[numParticles];
static float degree = 0;

Shape shapes[numShapes];

const GLfloat quadVertices[] = {
		-1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f,-1.0f, 0.0f,
		-1.0f,-1.0f, 0.0f
};

typedef enum
{
   CUBE,
   SPHERE,
} ShapeType;

#endif /* CONSTANTS_H_ */
