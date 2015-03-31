#include <GL/glut.h>
#include "transformations.h"
#include <cmath>
void rotMatrix(int theta,int axis,float affine[4][4])
{
	float rad = theta*(3.14/180.0);
	float s,c;
	s = sin(rad);
	c = cos(rad);
	if(axis==0)
	{
		float temp[4][4] = {{1.0,0,0,0},{0,c,-s,0},{0,s,c,0},{0,0,0,1.0}};
		for(int i=0;i<4;i++)
			for(int j=0;j<4;j++)
				affine[i][j] = temp[i][j];
	}
	else if(axis==1)
	{
		float temp[4][4] = {{c,0,s,0},{0,1.0,0,0},{-s,0,c,0},{0,0,0,1.0}};
		for(int i=0;i<4;i++)
			for(int j=0;j<4;j++)
				affine[i][j] = temp[i][j];
	}
	else if(axis==2)
	{
		float temp[4][4] = {{c,-s,0,0},{s,c,0,0},{0,0,1.0,0},{0,0,0,1.0}};
		for(int i=0;i<4;i++)
			for(int j=0;j<4;j++)
				affine[i][j] = temp[i][j];
	}
}
void applyTransform(float curMat[4][4],float affine[4][4])
{
	int i,j,k;
	float temp[4][4];
	for (i = 0; i < 4; ++i)
		for (j = 0; j < 4; ++j)
		{
			temp[i][j] = 0.0;
			for (k = 0; k < 4; ++k)
				temp[i][j] += curMat[i][k]*affine[k][j]; 
		}
	for (i = 0; i < 4; ++i)
		for (j = 0; j < 4; ++j)
			curMat[i][j] = temp[i][j];
}