#include "RubicksCube.hpp"
void assign(int n,int*** cubeBlockNo)
{
	int counter =0;
	for (int i = 0; i < n; ++i)
	{
		if(i==0 || i==n-1)
			for (int j=0;j<n;j++)
				for(int k=0;k<n;k++)
					cubeBlockNo[i][j][k] = counter++;
		else
		{
			for(int j=0;j<n;j++)
			{
				if(j=0 || j==n-1)
					for (int k = 0; k < n; ++k)
						cubeBlockNo[i][j][k] = counter++;
				else
				{
					cubeBlockNo[i][j][0] = counter++;
					cubeBlockNo[i][j][n-1] = counter++;
				}
			}
		}
	}
}
RCube::RCube(int n,int s)
{
	int no = (2*n+2*(n-2))*(n-2)+2*n*n;
	size =s;
	/* creating a map for the blocks in 3d space (cubeBlockNo)*/
	int ***cubeBlockNo = new int**[n];
	for (int i = 0; i < n; ++i)
	{
		cubeBlockNo[i] = new int*[n];
		for (int j = 0; j < n; ++j)
			cubeBlockNo[i][j] = new int[n];
	}
	assign(n,cubeBlockNo);
	initializeCubes();
	/* creating the cubes to fit in rubicks cube*/
	blocks = new Cube[no];

	/* creating the space for storing the face cube no map*/
	for(int i=0;i<6;i++)
		faceBlocks[i] = new int[n*n];
	
	/*Initial faceBlocks map*/

	for (int i = 0,int counter=0; i < n; ++i)
	{
		for(int j=0;j<n;j++)
		{
			int num = cubeBlockNo[i][j][0];
			faceBlocks[0][counter++] = num;
			blocks[num].setColor(0,Color[0]);
		}
	}
	for (int i = 0,int counter=0; i < n; ++i)
	{
		for(int j=0;j<n;j++)
		{
			int num = cubeBlockNo[i][j][n-1];
			faceBlocks[1][counter++] = num;
			blocks[num].setColor(1,Color[1]);
		}
	}
	for (int i = 0,int counter=0; i < n; ++i)
	{
		for(int k=0;k<n;k++)
		{
			int num = cubeBlockNo[i][n-1][k];
			faceBlocks[2][counter++] = num;
			blocks[num].setColor(2,Color[2]);
		}
	}
	for (int i = 0,int counter=0; i < n; ++i)
	{
		for(int k=0;k<n;k++)
		{
			int num = cubeBlockNo[i][0][k];
			faceBlocks[3][counter++] = num;
			blocks[num].setColor(3,Color[3]);
		}
	}
	for (int j = 0,int counter=0; j < n; ++j)
	{
		for(int k=0;k<n;k++)
		{
			int num = cubeBlockNo[n-1][j][k];
			faceBlocks[4][counter++] = num;
			blocks[num].setColor(4,Color[4]);
		}
	}
	for (int j = 0,int counter=0; j < n; ++j)
	{
		for(int k=0;k<n;k++)
		{
			int num = cubeBlockNo[0][j][k];
			faceBlocks[5][counter++] = num;
			blocks[num].setColor(5,Color[5]);
		}
	}

}
void Cube::initializeCubes()
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
					center[1] = -float(i-sub)*(size/float(n));
					blocks[counter++].initialize(center,size/n);
				}
		else
		{
			for(int j=0;j<n;j++)
			{
				if(j=0 || j==n-1)
					for (int k = 0; k < n; ++k)
					{
						center[0] = float(k-sub)*(size/float(n));
						center[1] = -float(j-sub)*(size/float(n));
						center[1] = -float(i-sub)*(size/float(n));
						blocks[counter++].initialize(center,size/n);
					}
				else
				{
					k = 0;
					center[0] = float(k-sub)*(size/float(n));
					center[1] = -float(j-sub)*(size/float(n));
					center[1] = -float(i-sub)*(size/float(n));
					blocks[counter++].initialize(center,size/n);
					k = n-1;
					center[0] = float(k-sub)*(size/float(n));
					center[1] = -float(j-sub)*(size/float(n));
					center[1] = -float(i-sub)*(size/float(n));
					blocks[counter++].initialize(center,size/n);
				}
			}
		}
	}
}
void display()
{
	int no = (2*n+2*(n-2))*(n-2)+2*n*n;
	for (int i = 0; i < no; ++i)
		blocks[no].render();
}