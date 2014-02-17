#ifndef CONFIGS_H_
#define CONFIGS_H_

#include "Node.h"
#include "Particle.h"
#include <math.h>
#include <cstdlib>

class Configs{
public:
    static Particle random_confic_particles(int x, int xSize, int ySize);
    
    static Node random_config_nodes(int x, int y);
    static Node towards_center_nodes(int x, int y, int ySize);
    static Node towards_center_2_nodes(int x, int y, int ySize);
};

#endif