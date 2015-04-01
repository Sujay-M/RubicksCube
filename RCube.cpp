#include <GL/glut.h>
#include "RCube.hpp"
GLfloat Color[6][3] = {{1,0,0},{0,1,0},{0,0,1},{1,1,0},{1,0,1},{1,1,1}};

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
	int counter =0;int sub=n/2;
	GLfloat center[3] = {0,0,0};
	outLine.initialize(center,size);
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
	for(int i=0;i<6;i++)
		faceBlocks[i] = new int[n*n];
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

	for (int i = 0, counter = 0; i < n; ++i)
		for(int j=0;j<n;j++)
		{
			int num = cubeBlockNo[i][j][0];
			faceBlocks[0][counter++] = num;
			blocks[num].setColor(0,Color[0]);
		}
	for (int i = 0, counter = 0; i < n; ++i)
		for(int j=0;j<n;j++)
		{
			int num = cubeBlockNo[i][j][n-1];
			faceBlocks[1][counter++] = num;
			blocks[num].setColor(1,Color[1]);
		}
	for (int i = 0, counter = 0; i < n; ++i)
		for(int k=0;k<n;k++)
		{
			int num = cubeBlockNo[i][n-1][k];
			faceBlocks[2][counter++] = num;
			blocks[num].setColor(2,Color[2]);
		}
	for (int i = 0, counter = 0; i < n; ++i)
		for(int k=0;k<n;k++)
		{
			int num = cubeBlockNo[i][0][k];
			faceBlocks[3][counter++] = num;
			blocks[num].setColor(3,Color[3]);
		}
	for (int j = 0, counter = 0; j < n; ++j)
		for(int k=0;k<n;k++)
		{
			int num = cubeBlockNo[n-1][j][k];
			faceBlocks[4][counter++] = num;
			blocks[num].setColor(4,Color[4]);
		}
	for (int j = 0, counter = 0; j < n; ++j)
		for(int k=0;k<n;k++)
		{
			int num = cubeBlockNo[0][j][k];
			faceBlocks[5][counter++] = num;
			blocks[num].setColor(5,Color[5]);
		}
}

void RCube::display(GLenum mode,int num)
{
	int no = (2*n+2*(n-2))*(n-2)+2*n*n;
	if (num==-1)
		for (int i = 0; i < no; ++i)
		{
			blocks[i].render(mode,i);
			blocks[i].drawOutLine(mode,i);
		}
	else
		for (int i = 0; i < 9; ++i)
		{
			blocks[faceBlocks[num][i]].render(mode,-1);
			blocks[faceBlocks[num][i]].drawOutLine(mode,-1);
		}
	outLine.drawOutLine(mode,no,TRUE);
	if(mode==GL_SELECT)
		outLine.drawOutLine(mode,no,TRUE);
}
void RCube::getBlockPts(float pts[24][3],int num)
{
	blocks[num].getPoints(pts);
}

void RCube::faceInfo(int sel,int selF[],int fc,int &final)
{
	for (int i = 0; i < 6; ++i)
		for (int j = 0; j < 9; ++j)
			if(faceBlocks[i][j]==sel)
				for (int k = 0; k < fc; ++k)
					if(i==selF[k])
						final = i;
}
void RCube::rotateFace(float affine[4][4],int face)
{
	for (int i = 0; i < 9; ++i)
		blocks[faceBlocks[face][i]].rotate(affine);
	//change codeblocknum and face map
}