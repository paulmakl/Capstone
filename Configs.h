#ifndef CONFIGS_H_
#define CONFIGS_H_

#include "Node.h"
#include "Particle.h"
#include "Randy.h"
#include <math.h>
#include <cstdlib>

class Configs{
public:
    static Particle random_config_particles(int xSize, int ySize, int zSize);
    static Particle random_snowball_particles(int radius, Vec3 center);
    
    
    static Node random_config_nodes(int x, int y, int z);
    static Node towards_center_nodes(int x, int y, int ySize);
    static Node towards_center_2_nodes(int x, int y, int ySize);
    static Node up_nodes(int x, int y);
    static Node dead_config_nodes();
};

#endif
