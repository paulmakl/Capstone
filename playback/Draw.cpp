#include "Draw.h"

void Draw::init(video *vi){
    vid = vi;
}

void Draw::displayGrid(){
    glPointSize(2.0);
	glBegin(GL_POINTS);
	Vec4 color;
	for(int x = 0; x < vid ->size.x; x++)
	{
		for(int y = 0; y < vid ->size.y; y++)
		{
			for(int z = 0; z < vid ->size.z; z++)
			{
				glColor4f(0.2, 0.2, 0.2, 1.0);
				glVertex3f(x, y, z);
			}
		}
	}
	glEnd();
}

void Draw::displayBackdrop()
{
	glBegin(GL_QUADS); // Start drawing a quad primitive
    glColor3f(0.1f, 0.1f, 0.1f);
    glVertex3f(0.0f, 0.0f, 0.0f); // The bottom left corner
    glVertex3f(vid->size.x, 0.0f, 0.0f); // The bottom right corner
    glVertex3f(vid->size.x, 0.0f, vid->size.z); // The top right corner
    glVertex3f(0.0f, 0.0f, vid->size.z); // The top left corner
    
	glEnd();
}

void Draw::displayParticles(int state)
{
	glPointSize(1.0);
	Vec3 position;
	//glColor3f(1.0f, 1.0f, 1.0f);
	float color = 1.0f;
	glBegin(GL_POINTS);
    
	for(int i = 0; i < vid ->states[state].particles.size(); i++)
	{
		particle* cur;
		cur = &vid->states[state].particles[i];
        
		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(cur->pos.x, cur ->pos.y, cur->pos.z);
	}
	glEnd();
}