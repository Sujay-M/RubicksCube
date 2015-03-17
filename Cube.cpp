#include "Cube.hpp"
#include "Points.hpp"

Cube::Cube()
{
	return;
}
Cube::Cube(GLfloat center[],int size,GLfloat col[][3])
{
	initialize(center,size,col);
}
void Cube::initialize(GLfloat center[],int size,GLfloat col[][3])
{
	GLfloat dummy[4][3];
	int index,indexA,indexB,toggleA,toggleB;
	for(int i=0;i<6;i++)
	{
		index = (i&(~1))/2;
		indexA = (index+1)%3;
		indexB = (index+2)%3;
		toggleA=toggleB=-1;
		for(int j=0;j<4;j++)
		{
			dummy[j][index] = center[index] + (i&1)*size -(size/2);
			dummy[j][indexA] = center[indexA] + toggleA*size/2;
			dummy[j][indexB] = center[indexB] + toggleB*size/2;			
			if((j+1)&1)
				toggleA*=-1;
			if((j+1)>1)
				toggleB = 1;
			face[i][j].setPoint(dummy[j]);
		}
	}
	for(int j=0;j<6;j++)
		for(int i=0;i<3;i++)
			color[j][i] = col[j][i];
}
void Cube::render()
{
	GLfloat vertex[3];	
	for(int i=0;i<6;i++)
	{
		glColor3fv(color[i]);
		glBegin(GL_POLYGON);
		for(int j=0;j<4;j++)
		{
			face[i][j].getpoint(vertex);
			glVertex3fv(vertex);
		}
		glEnd();
	}	
}
