#include <GL/glut.h>
#include "Cube.hpp"
// #include "Points.hpp"

Cube::Cube()
{
	cout<<"in Cube default constructor"<<endl;
	return;
}
Cube::Cube(GLfloat center[],int size)
{
	cout<<"in Cube parameterised constructor"<<endl;
	initialize(center,size);
}
void Cube::initialize(GLfloat center[],int size)
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

}
void Cube::render()
{
	GLfloat vertex[3];	
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
		glColor3f(0.0,0.0,0.0);
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
void Cube::displayPoints()
{
	for(int i=0;i<6;i++)
	{
		cout<<"face "<<i<<endl;
		cout<<face[i][0]<<face[i][1]<<face[i][2]<<face[i][3];
	}
}
void Cube::displayColor()
{
	for (int i = 0; i < 6; ++i)
	{
		cout<<"face "<<i<<endl;
		cout<<"( "<<color[i][0]<<" , "<<color[i][1]<<" , "<<color[i][2]<<" ) "<<endl;
	}
}