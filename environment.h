#ifndef ENVIRONMENT_H_
#define ENVIRONMENT_H_

#include "Grid.h"
#include "Particle.h"
#include "Shape.h"
<<<<<<< HEAD
#include "vectors.h"
#include <math.h>
#include <cstdlib>

#define xSize 64
#define ySize 64 // For now, keep xSize and ySize the same!
#define numParticles 100000
#define numShapes 1

class Environment{
public:
	Node grid[64][64];
	void generateNodes();

    Particle particles[1000];
    void generateParticles();

    Shape shapes[1];
};

#endif
=======

class Environment{
public:
    
    Particle particles[1000];
    Shape shapes[1];
    
};

#endif
>>>>>>> 7c40d12ca73902e6aa832c090e28c900f5c17c32
