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
		int di,dj,dk,ci,cj,ck;
		int *render = new int[no];
		for (int i = 0; i < no; ++i)
			render[i] = 0;
		di = !((num==4)|(num==5));
		dj = !((num==2)|(num==3));
		dk = !((num==0)|(num==1));
		ci = (n-1)*(num==4);
		cj = (n-1)*(num==2);
		ck = (n-1)*(num==1);
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n; ++j)	
			{
				int temp = cubeBlockNo[di*i+(!di)*ci][dj*dk*i+(!dk)*dj*j+(!dj)*cj][dk*j+(!dk)*ck];
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
int RCube::initRotateFace(int sel[],int num,int faceB[],int fc,int &selectedFace)
{
	int f[2] = {-1,-1},count=0,finalf=-1;
	int i,j,k,l,final=-1;
	if(num==n)
	{
	for (i = 0; i < 6; ++i)
	{
		int di,dj,dk,ci,cj,ck;
			di = !((i==4)|(i==5));
			dj = !((i==2)|(i==3));
			dk = !((i==0)|(i==1));
			ci = (n-1)*(i==4);
			cj = (n-1)*(i==2);
			ck = (n-1)*(i==1);
			int check = 0;
			for (int a = 0; a < n; ++a)
				for (int b = 0; b < n; ++b)

					for (k = 0; k < num; ++k)
						if(cubeBlockNo[di*a+(!di)*ci][dj*dk*a+(!dk)*dj*b+(!dj)*cj][dk*b+(!dk)*ck]==sel[k])
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
	int face = (finalf==f[0])?f[1]:f[0];
	for (i = 0; i < num; ++i)
		if(cubeBlockNo[di*i+ci][dj*i+cj][dk*i+ck]!=sel[i])
			break;
	switch(face)
	{
		case 0:
			if((i>=num && ((ci==0&&dj==1)||(cj==n-1&&di==1)))||(i<num && ((ci==n-1&&dj==1)||(cj==0&&di==1))))
				clk = 1;
			else
				clk = 0;
			break;
		case 1:
			if((i>=num && ((ci==n-1&&dj==1)||(cj==0&&di==1)))||(i<num && ((ci==0&&dj==1)||(cj==n-1&&di==1))))
				clk = 1;
			else
				clk = 0;
			break;
		case 2:
			if((i>=num && ((ci==0&&dk==1)||(ck==n-1&&di==1)))||(i<num && ((ci==n-1&&dk==1)||(ck==0&&di==1))))
				clk = 1;
			else
				clk = 0;
			break;
		case 3:
			if((i>=num && ((ci==n-1&&dk==1)||(ck==0&&di==1)))||(i<num && ((ci==0&&dk==1)||(ck==n-1&&di==1))))
				clk = 1;
			else
				clk = 0;
			break;
		case 4:
			if((i>=num && ((cj==n-1&&dk==1)||(ck==0&&dj==1)))||(i<num && ((cj==0&&dk==1)||(ck==n-1&&dj==1))))
				clk = 1;
			else
				clk = 0;
			break;
		case 5:
			if((i>=num && ((cj==0&&dk==1)||(ck==n-1&&dj==1)))||(i<num && ((cj==n-1&&dk==1)||(ck==0&&dj==1))))
				clk = 1;
			else
				clk = 0;
			break;
	}
	cout<<"i = "<<i<<"face = "<<face<<" rotation clk = "<<clk<<endl;
	if (face!=-1)
	{
		selectedFace = face;
		return clk;
	}
	// {

	// 	animate(face,clk);
	// 	rotateFace(face,clk);
	// }
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
	switch(face)
	{
		case 0:
			for (int i = 0; i < n; ++i)
				for(int j=0;j<n;j++)
					temp2[j][i] = temp1[j][i] = cubeBlockNo[n-1-i][j][0];
			break;
		case 1:

			for (int i = 0; i < n; ++i)
				for(int j=0;j<n;j++)
					temp2[j][i] = temp1[j][i] = cubeBlockNo[i][j][n-1];
			
			break;
		case 2:
			for (int i = 0; i < n; ++i)
				for(int j=0;j<n;j++)
					temp2[i][j] = temp1[i][j] = cubeBlockNo[i][n-1][j];
			
			break;
		case 3:
			for (int i = 0; i < n; ++i)
				for(int j=0;j<n;j++)
					temp2[i][j] = temp1[i][j] = cubeBlockNo[n-1-i][0][j];			
			break;
		case 4:
			for (int i = 0; i < n; ++i)
				for(int j=0;j<n;j++)
					temp2[i][j] = temp1[i][j] = cubeBlockNo[n-1][i][n-1-j];
			break;
		case 5:
			for (int i = 0; i < n; ++i)
				for(int j=0;j<n;j++)
					temp2[i][j] = temp1[i][j] = cubeBlockNo[0][i][j];
			break;
	}				
	rotateMatrix(temp1,clockWise,n);
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
		{
			for (int k = 0; k < 4; ++k)
				blocks[temp1[i][j]].getColor(rotOrder[face][k],col[i][j][k]);
			blocks[temp1[i][j]].getColor(noRotate[face][0],col[i][j][4]);
			blocks[temp1[i][j]].getColor(noRotate[face][1],col[i][j][5]);
		}
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			for (int k = 0; k < 4; ++k)
			{
				if(clockWise)
					blocks[temp2[i][j]].setColor(rotOrder[face][(k+1)%4],col[i][j][k]);
				else
					blocks[temp2[i][j]].setColor(rotOrder[face][(3+k)%4],col[i][j][k]);	
				blocks[temp2[i][j]].setColor(noRotate[face][0],col[i][j][4]);
				blocks[temp2[i][j]].setColor(noRotate[face][1],col[i][j][5]);	
			}	
}