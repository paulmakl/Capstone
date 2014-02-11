#include "Grid.h"

void Grid::init(float xSize, float ySize){
    grid.resize(xSize);
    
    for (int i = 0; i < grid.size(); i++) {
        grid[i].resize(ySize);
    }
    
    int x, y;
	float r, g, b;
	float forceX, forceY;
	forceX = 0.0;//0.064;
	for(x = 0; x < xSize; x++)
	{
		forceY = 0.0f;
		for(y = 0; y < ySize; y++)
		{
			Node a;
			r = 0.2f + rand()%30/100.0f;
			g = 0.2f + rand()%30/100.0f;
			b = 0.2f + rand()%30/100.0f;
			a.setRGBA(r, g, b, 1.0f);
			a.setForce(forceX + rand()%100/1000.0f - 0.055f, forceY + rand()%100/1000.0f - 0.055f); //, rand()%100/1000.0f - 0.055f);
            //a.setForce(0.02, 0.02);
			grid[x][y] = a;
			//forceY += 0.002f;
		}
		//forceX += 0.002f;
	}
}