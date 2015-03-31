#include <GL/glut.h>
#include "RubicksCube.hpp"
GLfloat Color[6][3] = {{1,0,0},{0,1,0},{0,0,1},{1,1,0},{1,0,1},{1,1,1}};;

RCube::RCube()
{
	return;
}

RCube::RCube(int SqMsize,int s)
{
	init(SqMsize,s);
}

void RCube::initializeCubes()
{
	int counter =0;int sub=n/2;GLfloat center[3];
	for (int i = 0; i < n; ++i)
	{
		if(i==0 || i==n-1)
			for (int j=0;j<n;j++)
				for(int k=0;k<n;k++)
				{
					center[0] = float(k-sub)*(size/float(n));
					center[1] = -float(j-sub)*(size/float(n));
					center[2] = -float(i-sub)*(size/float(n));
					cubeBlockNo[i][j][k] = counter;
					blocks[counter++].initialize(center,size/float(n));
				}
		else
		{
			for(int j=0;j<n;j++)
			{
				if(j==0 || j==n-1)
					for (int k = 0; k < n; ++k)
					{
						center[0] = float(k-sub)*(size/float(n));
						center[1] = -float(j-sub)*(size/float(n));
						center[2] = -float(i-sub)*(size/float(n));
						cubeBlockNo[i][j][k] = counter;
						blocks[counter++].initialize(center,size/float(n));
					}
				else
				{
					int k = 0;
					center[0] = float(k-sub)*(size/float(n));
					center[1] = -float(j-sub)*(size/float(n));
					center[2] = -float(i-sub)*(size/float(n));
					cubeBlockNo[i][j][k] = counter;
					blocks[counter++].initialize(center,size/float(n));
					k = n-1;
					center[0] = float(k-sub)*(size/float(n));
					center[1] = -float(j-sub)*(size/float(n));
					center[2] = -float(i-sub)*(size/float(n));
					cubeBlockNo[i][j][k] = counter;
					blocks[counter++].initialize(center,size/float(n));
				}
			}
		}
	}
}

void RCube::init(int SqMsize,int s)
{	
	size =s;
	n = SqMsize;
	int no = (2*n+2*(n-2))*(n-2)+2*n*n;

	/* creating a map for the blocks in 3d space (cubeBlockNo)*/
	cubeBlockNo = new int**[n];
	for (int i = 0; i < n; ++i)
	{
		cubeBlockNo[i] = new int*[n];
		for (int j = 0; j < n; ++j)
			cubeBlockNo[i][j] = new int[n];
	}
	blocks = new Cube[no];	
	initializeCubes();
	
	/*setting Color for cube faces*/

	for (int i = 0; i < n; ++i)
		for(int j=0;j<n;j++)
			blocks[cubeBlockNo[i][j][0]].setColor(0,Color[0]);
	for (int i = 0; i < n; ++i)
		for(int j=0;j<n;j++)
			blocks[cubeBlockNo[i][j][n-1]].setColor(1,Color[1]);
	for (int i = 0; i < n; ++i)
		for(int k=0;k<n;k++)
			blocks[cubeBlockNo[i][n-1][k]].setColor(2,Color[2]);
	for (int i = 0; i < n; ++i)
		for(int k=0;k<n;k++)
			blocks[cubeBlockNo[i][0][k]].setColor(3,Color[3]);
	for (int j = 0; j < n; ++j)
		for(int k=0;k<n;k++)
			blocks[cubeBlockNo[n-1][j][k]].setColor(4,Color[4]);
	for (int j = 0; j < n; ++j)
		for(int k=0;k<n;k++)
			blocks[cubeBlockNo[0][j][k]].setColor(5,Color[5]);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	display(GL_RENDER);
	glPushMatrix();
	// for (int i = 0; i < n; ++i)
	// {
	// 	cout<<i<<"th square"<<endl;
	// 	for (int j = 0; j < n; ++j)
	// 	{
	// 		for (int k = 0; k < n; ++k)
	// 		{
	// 			cout<<cubeBlockNo[i][j][k]<<"  ";
	// 		}
	// 		cout<<endl;
	// 	}

	// }
}

void RCube::display(GLenum mode)
{
	int no = (2*n+2*(n-2))*(n-2)+2*n*n;
	for (int i = 0; i < no; ++i)
		blocks[i].render(mode,i);
}

void RCube::rotateFace(int ,int )
{
	
}

void RCube::Transform(float affine[4][4])
{
	int no = (2*n+2*(n-2))*(n-2)+2*n*n;
	for (int i = 0; i < no; ++i)
		blocks[i].rotate(affine);
}
void RCube::getBlockPts(float pts[24][3],int num)
{
	blocks[num].getPoints(pts);
}