#ifndef ENVIRONMENT_H_
#define ENVIRONMENT_H_

#include "Grid.h"
#include "Particle.h"
#include "Shape.h"
#include "vectors.h"
#include "Cube.h"
#include <math.h>
#include <cstdlib>

#define xSize 64
#define ySize 64 // For now, keep xSize and ySize the same!
#define numParticles 100000
#define numShapes 1

class Environment{
public:
	Node grid[xSize][ySize];
	Particle particles[numParticles];
	Cube shapes[numShapes];

	void generateNodes();
	void generateParticles();
	void generateShapes();
};

#endif
