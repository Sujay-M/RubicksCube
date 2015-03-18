#include <GL/glut.h>
#include "RubicksCube.hpp"
GLfloat Color[6][3] = {{1,0,0},{0,1,0},{0,0,1},{1,1,0},{1,0,1},{0,1,1}};;
void assign(int n,int*** cubeBlockNo)
{
	// cout<<"in assign n="<<n<<endl;
	int counter =0;
	for (int i = 0; i < n; ++i)
	{
		// cout<<"i = "<<i<<endl;
		if(i==0 || i==n-1)
			for (int j=0;j<n;j++)
				for(int k=0;k<n;k++)
					cubeBlockNo[i][j][k] = counter++;
		else
		{
			for(int j=0;j<n;j++)
			{
				if(j==0 || j==n-1)
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
RCube::RCube(int SqMsize,int s)
{
	// cout<<"in RCube constructor"<<endl;
	
	size =s;
	n = SqMsize;
	int no = (2*n+2*(n-2))*(n-2)+2*n*n;
	/* creating a map for the blocks in 3d space (cubeBlockNo)*/
	int ***cubeBlockNo = new int**[n];
	for (int i = 0; i < n; ++i)
	{
		cubeBlockNo[i] = new int*[n];
		for (int j = 0; j < n; ++j)
			cubeBlockNo[i][j] = new int[n];
	}
	blocks = new Cube[no];
	// cout<<"initializing"<<endl;
	assign(n,cubeBlockNo);
	initializeCubes();
	// cout<<"initializing cubes done"<<endl;
	/* creating the cubes to fit in rubicks cube*/
	

	/* creating the space for storing the face cube no map*/
	for(int i=0;i<6;i++)
		faceBlocks[i] = new int[n*n];
	
	/*Initial faceBlocks map*/

	for (int i = 0,counter=0; i < n; ++i)
	{
		for(int j=0;j<n;j++)
		{
			int num = cubeBlockNo[i][j][0];
			faceBlocks[0][counter++] = num;
			blocks[num].setColor(0,Color[0]);
		}
	}
	// cout<<"face 0 map creation done"<<endl;
	for (int i = 0,counter=0; i < n; ++i)
	{
		for(int j=0;j<n;j++)
		{
			int num = cubeBlockNo[i][j][n-1];
			faceBlocks[1][counter++] = num;
			blocks[num].setColor(1,Color[1]);
		}
	}
	// cout<<"face 1 map creation done"<<endl;
	for (int i = 0,counter=0; i < n; ++i)
	{
		for(int k=0;k<n;k++)
		{
			int num = cubeBlockNo[i][n-1][k];
			faceBlocks[2][counter++] = num;
			blocks[num].setColor(2,Color[2]);
		}
	}
	// cout<<"face 2 map creation done"<<endl;
	for (int i = 0,counter=0; i < n; ++i)
	{
		for(int k=0;k<n;k++)
		{
			int num = cubeBlockNo[i][0][k];
			faceBlocks[3][counter++] = num;
			blocks[num].setColor(3,Color[3]);
		}
	}
	// cout<<"face 3 map creation done"<<endl;
	for (int j = 0,counter=0; j < n; ++j)
	{
		for(int k=0;k<n;k++)
		{
			int num = cubeBlockNo[n-1][j][k];
			faceBlocks[4][counter++] = num;
			blocks[num].setColor(4,Color[4]);
		}
	}
	// cout<<"face 4 map creation done"<<endl;
	for (int j = 0,counter=0; j < n; ++j)
	{
		for(int k=0;k<n;k++)
		{
			int num = cubeBlockNo[0][j][k];
			faceBlocks[5][counter++] = num;
			blocks[num].setColor(5,Color[5]);
		}
	}
	// cout<<"face 5 map creation done"<<endl;
	delete(cubeBlockNo);
}
void RCube::initializeCubes()
{
	// cout<<"in initializeCubes"<<endl;
	int counter =0;int sub=n/2;GLfloat center[3];
	for (int i = 0; i < n; ++i)
	{
		// cout<<"i = "<<i<<endl;
		if(i==0 || i==n-1)
			for (int j=0;j<n;j++)
				for(int k=0;k<n;k++)
				{
					// cout<<"k = "<<k<<endl;
					center[0] = float(k-sub)*(size/float(n));
					center[1] = -float(j-sub)*(size/float(n));
					center[2] = -float(i-sub)*(size/float(n));
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
						blocks[counter++].initialize(center,size/float(n));
					}
				else
				{
					int k = 0;
					center[0] = float(k-sub)*(size/float(n));
					center[1] = -float(j-sub)*(size/float(n));
					center[2] = -float(i-sub)*(size/float(n));
					blocks[counter++].initialize(center,size/float(n));
					k = n-1;
					center[0] = float(k-sub)*(size/float(n));
					center[1] = -float(j-sub)*(size/float(n));
					center[2] = -float(i-sub)*(size/float(n));
					blocks[counter++].initialize(center,size/float(n));
				}
			}
		}
	}
}
void RCube::display()
{
	int no = (2*n+2*(n-2))*(n-2)+2*n*n;
	// cout<<"n = "<<n<<"no = "<<no<<endl;
	// for (int i = 0; i < no; ++i)
	// {
	// 	// cout<<"displaying cube "<<i<<endl;
	// 	// // blocks[no].render();
	// 	// blocks[no].displayPoints();
	// 	cout<<"i="<<i<<endl;
	// 	blocks[no].displayPoints();
	// }
	// blocks[0].displayPoints();
	for (int i = 0; i < no; ++i)
		blocks[i].render();
	// blocks[1].displayColor();
}