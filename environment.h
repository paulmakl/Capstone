#ifndef ENVIRONMENT_H_
#define ENVIRONMENT_H_

#include "Grid.h"
#include "ParticleCollection.h"
#include "Shape.h"
#include "vectors.h"
#include "Cube.h"
#include <math.h>
#include <cstdlib>
#include <vector>

#define numShapes 1

class Environment{
public:

    int xSize;
    int ySize;
    int zSize;
    int numParticles;
    ParticleCollection particles;
    Grid grid;
    
    Environment();
	void generateNodes();
    
    void init(int x, int y,int z, int numPs);

    
    void generateParticles();

	Cube shapes[numShapes];

	void generateShapes();
    
    void sortParticles();
};
#endif
