#include "RCube.hpp"
#include "transformations.h"
GLfloat Color[6][3] = {{1,0,0},{0,1,0},{0,0,1},{1,1,0},{1,.5,0},{1,1,1}};
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
	int counter =0;
	float sub = (n%2!=0)?n/2:(float)(n-1)/2.0;
	GLfloat center[3] = {0,0,0};
	outLine.initialize(center,size);
	for (int i = 0; i < n; ++i)
	{
		if(i==0 || i==n-1)
			for (int j=0;j<n;j++)
				for(int k=0;k<n;k++)
				{
					center[0] = (float)(k-sub)*(size/(float)n);
					center[1] = -(float)(j-sub)*(size/(float)n);
					center[2] = -(float)(i-sub)*(size/(float)n);
					cubeBlockNo[i][j][k] = counter;
					blocks[counter++].initialize(center,size/(float)n);
				}
		else
		{
			for(int j=0;j<n;j++)
			{
				if(j==0 || j==n-1)
					for (int k = 0; k < n; ++k)
					{
						center[0] = (float)(k-sub)*(size/(float)n);
						center[1] = -(float)(j-sub)*(size/(float)n);
						center[2] = -(float)(i-sub)*(size/(float)n);
						cubeBlockNo[i][j][k] = counter;
						blocks[counter++].initialize(center,size/(float)n);
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
void RCube::initFaceblocks()
{

	int no = (2*n+2*(n-2))*(n-2)+2*n*n;
	for (int i = 0,count=0; i < n; ++i)
		for(int j=0;j<n;j++)
			faceBlocks[0][count++] = cubeBlockNo[n-1-j][i][0];
	for (int i = 0,count=0; i < n; ++i)
		for(int j=0;j<n;j++)
			faceBlocks[1][count++] = cubeBlockNo[j][i][n-1];
	for (int i = 0,count=0; i < n; ++i)
		for(int j=0;j<n;j++)
			faceBlocks[2][count++] = cubeBlockNo[i][n-1][j];
	for (int i = 0,count=0; i < n; ++i)
		for(int j=0;j<n;j++)
			faceBlocks[3][count++] = cubeBlockNo[n-1-i][0][j];			
	for (int i = 0,count=0; i < n; ++i)
		for(int j=0;j<n;j++)
			faceBlocks[4][count++] = cubeBlockNo[n-1][i][n-1-j];
	for (int i = 0,count=0; i < n; ++i)
		for(int j=0;j<n;j++)
			faceBlocks[5][count++] = cubeBlockNo[0][i][j];
	for (int k = 1; k < n-1; ++k)
	{
		for (int i = 0,count=0; i < n; ++i)
			for(int j=0;j<n;j++)
				if (cubeBlockNo[n-1-j][i][k]>=0 && cubeBlockNo[n-1-j][i][k]<no)
					faceBlocks[5+k][count++] = cubeBlockNo[n-1-j][i][k];
				else
					faceBlocks[5+k][count++] = -1;
				
	}
	for (int k = 1; k < n-1; ++k)
	{
		for (int i = 0,count=0; i < n; ++i)
			for(int j=0;j<n;j++)
				if (cubeBlockNo[n-1-i][k][j]>=0 && cubeBlockNo[n-1-i][k][j]<no)
					faceBlocks[5+n-2+k][count++] = cubeBlockNo[n-1-i][k][j];
				else
					faceBlocks[5+n-2+k][count++] = -1;
				
	}
	for (int k = 1; k < n-1; ++k)
	{
		for (int i = 0,count=0; i < n; ++i)
			for(int j=0;j<n;j++)
				if (cubeBlockNo[k][i][j]>=0 && cubeBlockNo[k][i][j]<no)
					faceBlocks[5+2*n-4+k][count++] = cubeBlockNo[k][i][j];
				else
					faceBlocks[5+2*n-4+k][count++] = -1;
				
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
	/* faceblocks map */
	faceBlocks = new int*[3*n];
	for (int i = 0; i < 3*n; ++i)
		faceBlocks[i] = new int[n*n];
	initFaceblocks();
	/*setting Color for cube faces*/
	for (int i = 0; i < no; ++i)
		for (int j = 0; j < 6; ++j)
			blocks[i].setColor(j,Color[j]);
}

void RCube::display(GLenum mode,int num,int flag)
{
	int no = (2*n+2*(n-2))*(n-2)+2*n*n;
	if (num==-1)
	{
		for (int i = 0; i < no; ++i)
			blocks[i].render(mode,i);
		if(mode==GL_SELECT)
			for (int i = 0; i < 6; ++i)
				outLine.drawFace(no,i);
	}
	else
	{	
		int *render = new int[no];
		for (int i = 0; i < no; ++i)
			render[i] = 0;
		for (int i = 0; i < n*n; ++i)
		{
			int temp = faceBlocks[num][i];
			if (temp!=-1)
				render[temp] = 1;
		}
		for (int i = 0; i < no; ++i)
			if(flag==1 && render[i]==1)
				blocks[i].render(mode,i);
			else if(flag==0 && render[i]==0)
				blocks[i].render(mode,i);
		if(mode==GL_SELECT)
			outLine.drawFace(no,num);			
	}

}
void RCube::getBlockPts(float pts[24][3],int num)
{
	blocks[num].getPoints(pts);
}
int RCube::initRotateFace(int sel[],int num,int faceB,int &selectedFace)
{
	int f[2] = {-1,-1},count=0,finalf=-1;
	int i,j,k,l,final=-1;
	if(num==n)
	{
	for (i = 0; i < 3*n; ++i)
	{
		int check = 0;
		for (int a = 0; a < n*n; ++a)
			for (k = 0; k < num; ++k)
				if(faceBlocks[i][a]==sel[k])
					check++;	
		if(check==num)
		{
			f[count++] = i;
			if(i==faceB)
				finalf = i;
		}
	}
	
	bool clk = FALSE;
	
	int face = (finalf==f[0])?f[1]:f[0];
	
	if (face!=-1)
	{
		
		int i,j;
		int **temp1 = new int*[n];
		for (i = 0; i < n; ++i)
			temp1[i] = new int[n];
		for (int i = 0,count=0; i < n; ++i)
		{	for(int j=0;j<n;j++)
			{
				temp1[i][j] = faceBlocks[face][count++];
			}
		}
		for (i = 0; i < n; ++i)
			if(temp1[0][i] != sel[i])
				break;
		if (i==n)
			clk = TRUE;
		for (i = 0; i < n; ++i)
			if(temp1[i][n-1] != sel[i])
				break;
		if (i==n)
			clk = TRUE;
		for (i = 0; i < n; ++i)
		{
			if(temp1[n-1][n-1-i] != sel[i])
				break;
		}
		if (i==n)
			clk = TRUE;
		for (i = 0; i < n; ++i)
			if(temp1[n-1-i][0] != sel[i])
				break;
		if (i==n)
			clk = TRUE;
		
		selectedFace = face;
		return clk;
	}
	}
	selectedFace = -1;
	return -1;	
}
void rotateMatrix(int **mat,int rev,int n)
{
	int i,j,k;
	if(rev==0)
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
	float ****col = new float***[n];
	int **temp1 = new int*[n];
	int **temp2 = new int*[n];
	int rotOrder[6][4] = {{3,5,2,4},{3,4,2,5},{5,1,4,0},{4,1,5,0},{3,0,2,1},{3,1,2,0}};
	int noRotate[6][2] = {{0,1},{0,1},{2,3},{2,3},{4,5},{4,5}};
	int order;
	for (int i = 0; i < n; ++i)
	{
		temp1[i] = new int[n];	
		temp2[i] = new int[n];
		col[i] = new float**[n];
		for (int j = 0; j < n; ++j)
		{
			col[i][j] = new float*[6];
			for (int k = 0; k < 6; ++k)
				col[i][j][k] = new float[3];
		}
		 
	}

	for (int i = 0,count=0; i < n; ++i)
		for(int j=0;j<n;j++)
			temp2[i][j] = temp1[i][j] = faceBlocks[face][count++];
					
	rotateMatrix(temp1,clockWise,n);
	if(face>=6)
	{
		switch((face-6)/(n-2))
		{
			case 0: order = 0;break;
			case 1: order = 3;break;
			case 2: order = 5;break;
		}
		
	}
	else
		order = face;
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
		{
			if (temp1[i][j]!=-1)
			{
				for (int k = 0; k < 4; ++k)
					blocks[temp1[i][j]].getColor(rotOrder[order][k],col[i][j][k]);
				
				blocks[temp1[i][j]].getColor(noRotate[order][0],col[i][j][4]);
				blocks[temp1[i][j]].getColor(noRotate[order][1],col[i][j][5]);
				
			}
			
		}
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			for (int k = 0; k < 4; ++k)
			{
				if (temp2[i][j]!=-1)
				{
					if(clockWise)
						blocks[temp2[i][j]].setColor(rotOrder[order][(k+1)%4],col[i][j][k]);
					else
						blocks[temp2[i][j]].setColor(rotOrder[order][(3+k)%4],col[i][j][k]);
					
						blocks[temp2[i][j]].setColor(noRotate[order][0],col[i][j][4]);
						blocks[temp2[i][j]].setColor(noRotate[order][1],col[i][j][5]);
						
					
				}
					
			}	
}

int RCube::winCheck()
{
	float col[3],check[3];
	for (int num = 0; num < 6; ++num)
	{
		blocks[faceBlocks[num][0]].getColor(num,check);
		for (int i = 0; i < n*n; ++i)
		{
			blocks[faceBlocks[num][i]].getColor(num,col);
			if(col[0]!=check[0]||col[1]!=check[1]||col[2]!=check[2])
				return 0;
		}			
	}
	return 1;	
}