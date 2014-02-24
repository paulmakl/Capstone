#include "Grid.h"

void Grid::init(float xSize, float ySize)
{
    grid.resize(xSize);
    
    for (int i = 0; i < (int)grid.size(); i++)
    {
        grid[i].resize(ySize);
    }
    //srand (time(NULL)); // Turn this off if you want a random value uniform across all simulations.

    int x, y;
	for(x = 0; x < xSize; x++)
	{
		for(y = 0; y < ySize; y++)
		{
			Node a;
            a = Configs::dead_config_nodes();
			grid[x][y] = a;
		}
	}
}
