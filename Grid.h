#ifndef GRID_H_
#define GRID_H_

#include "Node.h"
#include <math.h>
#include <cstdlib>
#include <vector>

//using std::vector;

class Grid{
    public:
        std::vector<std::vector<Node>> grid;
        void init(float a, float b);
};


#endif
