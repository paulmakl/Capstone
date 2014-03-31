#ifndef GRID_H_
#define GRID_H_

#include "Node.h"
#include "Configs.h"
#include <math.h>
#include <cstdlib>
#include <vector>

//using std::vector;

class Grid{
    public:
        std::vector<std::vector<std::vector<Node> > > grid;
        void init(float xSize, float ySize, float zSize);
};


#endif
