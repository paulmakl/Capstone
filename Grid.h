#ifndef GRID_H_
#define GRID_H_

#include "Node.h"
#include <math.h>
#include <cstdlib>
#include <vector>

//using std::vector;

class Grid{
    public:
        //Node grid[64][64];
        std::vector<std::vector<Node>> grid;
        void init(float a, float b);
    
};


#endif