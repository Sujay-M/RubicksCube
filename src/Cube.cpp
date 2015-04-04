#include "Cube.hpp"

Cube::Cube()
{
	return;
}
Cube::Cube(GLfloat center[],int size)
{
	initialize(center,size);
}
void Cube::setLattice(GLfloat center[],int size)
{
	GLfloat dummy[3];
	int toggleA,toggleB;
	toggleA=toggleB=-1;
	for (int i = 0; i < 4; ++i)
	{
		dummy[0] = center[0] + toggleA*size/2;
		dummy[1] = center[1] + toggleB*size/2;
		dummy[2] = center[2] + size/2;
		latticePts[i].setPoint(dummy);
		if((i+1)&1)
				toggleA*=-1;
		if((i+1)>1)
			toggleB = 1;
	}
	toggleA=toggleB=-1;
	for (int i = 4; i < 8; ++i)
	{
		dummy[0] = center[0] + toggleA*size/2;
		dummy[1] = center[1] + toggleB*size/2;
		dummy[2] = center[2] - size/2;
		latticePts[i].setPoint(dummy);
		if((i+1)&1)
				toggleA*=-1;
		if((i+1)>5)
			toggleB = 1;
	}

}
void Cube::initFromLattice()
{
	int faceNo[6][4] = {{0,4,7,3},{1,5,6,2},{1,5,4,0},{2,6,7,3},{4,5,6,7},{0,1,2,3}};
	float dummy[3];
	for (int i = 0; i < 6; ++i)
	{
		for(int j =0; j < 4; j++)
		{
			latticePts[faceNo[i][j]].getPoint(dummy);
			face[i][j].setPoint(dummy);
		}
	}
}

void Cube::initialize(GLfloat center[],int size)
{
	GLfloat dummy[4][3];
	setLattice(center,size);
	initFromLattice();
}
void Cube::render(GLenum mode, int num)
{
	GLfloat vertex[3];
	if (mode == GL_SELECT)	
		glLoadName(num);
	glLineWidth(3);	
	for(int i=0;i<6;i++)
	{
		glColor3f(color[i][0],color[i][1],color[i][2]);
		glBegin(GL_POLYGON);
		for(int j=0;j<4;j++)
		{
			face[i][j].getPoint(vertex);
			glVertex3fv(vertex);
		}
		glEnd();
	}	
}
void Cube::drawOutLine(GLenum mode, int num,bool numberFace)
{
	GLfloat vertex[3];
	glLineWidth(3);
	glColor3f(0.0,0.0,0.0);
	if (mode == GL_SELECT && !numberFace)	
		glLoadName(num);
	for(int i=0;i<6;i++)
	{
		if(mode == GL_SELECT && numberFace)
		{
			glLoadName(num+i);
			glBegin(GL_POLYGON);
		}
		else
			glBegin(GL_LINE_LOOP);

		for(int j=0;j<4;j++)
		{
			face[i][j].getPoint(vertex);
			glVertex3fv(vertex);
		}
		glEnd();
	}
}
void Cube::setColor(int no,GLfloat col[])
{
	for (int i = 0; i < 3; i++)
		color[no][i] = col[i];
}
void Cube::getColor(int no,GLfloat col[])
{
	for (int i = 0; i < 3; i++)
		col[i] = color[no][i];
}
void Cube::getPoints(float lattice[24][3])
{
	for (int i = 0; i < 6; ++i)
		for (int j = 0; j < 4; ++j)
			face[i][j].getPoint(lattice[i*4+j]);
}
void Cube::transform(float affine[4][4])
{
	for (int i = 0; i < 6; ++i)
		for(int j=0;j<4;j++)
			face[i][j]*affine;
}