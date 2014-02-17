#include "Grid.h"

void Grid::init(float xSize, float ySize){
    grid.resize(xSize);
    
    for (int i = 0; i < grid.size(); i++) {
        grid[i].resize(ySize);
    }
    srand (time(NULL)); // Turn this off if you want a random value uniform across all simulations.

    int x, y;
	//float r, g, b;
	//float forceX, forceY;
	//forceX = 0.0;//0.064;
	for(x = 0; x < xSize; x++)
	{
		//forceY = 0.0f;
		for(y = 0; y < ySize; y++)
		{
			Node a;
            a = Configs::random_config_nodes(x,y);
			grid[x][y] = a;
		}
	}
}