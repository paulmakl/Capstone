#ifndef ENVIRONMENT_H_
#define ENVIRONMENT_H_

#include "Grid.h"
#include "Particle.h"
#include "Shape.h"
#include "vectors.h"
#include <math.h>
#include <cstdlib>
#include <vector>

#define numShapes 1

class Environment{
public:
    int xSize;
    int ySize;
    int numParticles;
	//Node grid[64][64];
    
    Environment();
	void generateNodes();
    Grid grid;
    void init(int x, int y, int numPs);
    //Particle particles[1000];
    std::vector<Particle> particles;
    void generateParticles();

    Shape shapes[1];
};
#endif
