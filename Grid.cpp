#include "Grid.h"

void Grid::init(float xSize, float ySize, float zSize)
{
    grid.resize(xSize);
    
    for (int i = 0; i < (int)grid.size(); i++)
    {
    	grid[i].resize(ySize);
    	for(int j = 0; j < (int)grid.size(); j++)
    	{
    		grid[i][j].resize(zSize);
    	}
    }
    //srand (time(NULL)); // Turn this off if you want a random value uniform across all simulations.

    int x, y, z;
	for(x = 0; x < xSize; x++)
	{
		for(y = 0; y < ySize; y++)
		{
			for(z = 0; z < zSize; z++)
			{
				Node a;
				a = Configs::dead_config_nodes();
				grid[x][y][z] = a;
			}
		}
	}
}
