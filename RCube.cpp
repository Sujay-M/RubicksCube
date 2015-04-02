#include <GL/glut.h>
#include "RCube.hpp"
#include "transformations.h"
GLfloat Color[6][3] = {{1,0,0},{0,1,0},{0,0,1},{1,1,0},{1,0,1},{1,1,1}};

RCube::RCube()
{
	return;
}

RCube::RCube(int SqMsize,int s)
{
	init(SqMsize,s);
}
void RCube::initFaceMap()
{
	for (int i = 0, counter = 0; i < n; ++i)
		for(int j=0;j<n;j++)
			faceBlocks[0][counter++] = cubeBlockNo[i][j][0];
	for (int i = 0, counter = 0; i < n; ++i)
		for(int j=0;j<n;j++)
			faceBlocks[1][counter++] = cubeBlockNo[i][j][n-1];
	for (int i = 0, counter = 0; i < n; ++i)
		for(int j=0;j<n;j++)
			faceBlocks[2][counter++] = cubeBlockNo[i][n-1][j];
	for (int i = 0, counter = 0; i < n; ++i)
		for(int j=0;j<n;j++)
			faceBlocks[3][counter++] = cubeBlockNo[i][0][j];
	for (int i = 0, counter = 0; i < n; ++i)
		for(int j=0;j<n;j++)
			faceBlocks[4][counter++] = cubeBlockNo[n-1][i][j];
	for (int i = 0, counter = 0; i < n; ++i)
		for(int j=0;j<n;j++)
			faceBlocks[5][counter++] = cubeBlockNo[0][i][j];

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
			blocks[cubeBlockNo[i][j][0]].setColor(0,Color[0]);
	for (int i = 0, counter = 0; i < n; ++i)
		for(int j=0;j<n;j++)
			blocks[cubeBlockNo[i][j][n-1]].setColor(1,Color[1]);
	for (int i = 0, counter = 0; i < n; ++i)
		for(int k=0;k<n;k++)
			blocks[cubeBlockNo[i][n-1][k]].setColor(2,Color[2]);
	for (int i = 0, counter = 0; i < n; ++i)
		for(int k=0;k<n;k++)
			blocks[cubeBlockNo[i][0][k]].setColor(3,Color[3]);
	for (int j = 0, counter = 0; j < n; ++j)
		for(int k=0;k<n;k++)
			blocks[cubeBlockNo[n-1][j][k]].setColor(4,Color[4]);
	for (int j = 0, counter = 0; j < n; ++j)
		for(int k=0;k<n;k++)
			blocks[cubeBlockNo[0][j][k]].setColor(5,Color[5]);
	initFaceMap();
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

void RCube::rotFace(int sel[],int num,int faceB[],int fc)
{
	int f[2] = {-1,-1},count=0,finalf=-1;
	int i,j,k,l,final=-1;
	if(num==n)
	{
	for (i = 0; i < 6; ++i)
	{
		int check = 0;
		for (j = 0; j < 9; ++j)
			for (k = 0; k < num; ++k)
				if(faceBlocks[i][j]==sel[k])
					check++;
		if(check==num)
		{
			f[count++] = i;
			for (l = 0; l < fc; ++l)
				if(i==faceB[l])
					finalf = i;
		}
	}
	int di,dj,dk,ci,cj,ck;
	bool clk;
	di = !((f[0]==4)|(f[0]==5)|(f[1]==4)|(f[1]==5));
	dj = !((f[0]==2)|(f[0]==3)|(f[1]==2)|(f[1]==3));
	dk = !((f[0]==0)|(f[0]==1)|(f[1]==0)|(f[1]==1));
	ci = (n-1)*((f[0]==4)|(f[1]==4));
	cj = (n-1)*((f[0]==2)|(f[1]==2));
	ck = (n-1)*((f[0]==1)|(f[1]==1));
	cout<<"di = "<<di<<" dj = "<<dj<<" dk = "<<dk<<endl;
	cout<<"ci = "<<ci<<" cj = "<<cj<<" ck = "<<ck<<endl;
	for (i = 0; i < num; ++i)
		if(cubeBlockNo[di*i+ci][dj*i+cj][dk*i+ck]!=sel[i])
			break;
	if(i<num)
		clk = FALSE;
	else
		clk = TRUE;
	int face = (finalf==f[0])?f[1]:f[0];
	cout<<"face = "<<face<<" rotation clk = "<<clk<<endl;
	rotateFace(face,clk);
	}	
}
void rotateMatrix(int **mat,int rev,int n)
{
	int i,j,k;
	if(rev==1)
	{	
		for (k = 0; k < n/2; k++)
		{
			j = k;
			int *first = new int[n-k];
			for (j = k; j < n-k; ++j)
				first[j] = mat[k][j];
			for (j = k; j < n-k; ++j)
				mat[k][j] = mat[j][n-1-k];
			for (j = k;j<n-k;j++)
				mat[j][n-k-1] = mat[n-k-1][n-1-j];
			for (j=k;j<n-k;j++)
				mat[n-k-1][n-j-1] = mat[n-1-j][k];
			for (j=k;j<n-k;j++)
				mat[n-j-1][k] = first[j];
			delete(first);
		}
	}
	else
	{
		for (k = 0; k < n/2; k++)
		{
			j = k;
			int *first = new int[n-k];
			for (j = k; j < n-k; ++j)
				first[j] = mat[k][j];
			for (j = k; j < n-k; ++j)
				mat[k][j] = mat[n-1-j][k];
			for (j = k;j<n-k;j++)
				mat[j][k] = mat[n-k-1][j];
			for (j=k;j<n-k;j++)
				mat[n-k-1][j] = mat[n-1-j][n-1-k];
			for (j=k;j<n-k;j++)
				mat[j][n-k-1] = first[j];
			delete(first);
		}
	}
}
void RCube::rotateFace(int face,bool clockWise)
{
	float affine[4][4];
	int **temp = new int*[n];
	for (int i = 0; i < n; ++i)
		temp[i] = new int[n];
	switch(face)
	{
		case 0:
			for (int i = 0; i < n; ++i)
				for(int j=0;j<n;j++)
					temp[i][j] = cubeBlockNo[i][j][0];
			if(clockWise)
			{				
				rotMatrix(90,0,affine);
				rotateMatrix(temp,0,n);
				
			}			
			else
			{
				rotMatrix(-90,0,affine);
				rotateMatrix(temp,1,n);
			}
			for (int i = 0; i < n; ++i)
				for(int j=0;j<n;j++)
					cubeBlockNo[i][j][0] = temp[i][j];
			break;
		case 1:
			for (int i = 0; i < n; ++i)
				for(int j=0;j<n;j++)
					temp[i][j] = cubeBlockNo[i][j][n-1];
			if(clockWise)
			{
				rotMatrix(-90,0,affine);
				rotateMatrix(temp,0,n);
			}
			else
			{
				rotMatrix(90,0,affine);
				rotateMatrix(temp,1,n);
			}
			for (int i = 0; i < n; ++i)
				for(int j=0;j<n;j++)
					cubeBlockNo[i][j][n-1] = temp[i][j];
			break;
		case 2:
			for (int i = 0; i < n; ++i)
				for(int j=0;j<n;j++)
					temp[i][j] = cubeBlockNo[i][n-1][j];
			if(clockWise)
			{
				rotMatrix(90,1,affine);
				rotateMatrix(temp,0,n);
			}
			else
			{
				rotMatrix(-90,1,affine);
				rotateMatrix(temp,1,n);
			}
			for (int i = 0; i < n; ++i)
				for(int j=0;j<n;j++)
					cubeBlockNo[i][n-1][j] = temp[i][j];
			break;
		case 3:
			for (int i = 0; i < n; ++i)
				for(int j=0;j<n;j++)
					temp[i][j] = cubeBlockNo[i][0][j];
			if(clockWise)
			{
				rotMatrix(90,1,affine);
				rotateMatrix(temp,0,n);
			}
			else
			{
				rotMatrix(-90,1,affine);
				rotateMatrix(temp,1,n);
			}
			for (int i = 0; i < n; ++i)
				for(int j=0;j<n;j++)
					cubeBlockNo[i][0][j] = temp[i][j];
			break;
		case 4:
			if(clockWise)
			{
				rotMatrix(-90,2,affine);
				rotateMatrix(cubeBlockNo[0],1,n);
			}
			else
			{
				rotMatrix(90,2,affine);
				rotateMatrix(cubeBlockNo[0],0,n);
			}
			break;
		case 5:
			if(clockWise)
			{
				rotMatrix(90,2,affine);
				rotateMatrix(cubeBlockNo[n-1],0,n);
			}
			else
			{
				rotMatrix(-90,2,affine);
				rotateMatrix(cubeBlockNo[n-1],1,n);
			}
			break;
	}

	for (int i = 0; i < 9; ++i)
		blocks[faceBlocks[face][i]].rotate(affine);
	//change codeblocknum and face map
	initFaceMap();
}