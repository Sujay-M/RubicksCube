#include <GL/glut.h>
#include "Cube.hpp"
class RCube
{
	int n,size,***cubeBlockNo,*faceBlocks[6];
	Cube *blocks;
	
	public:
		RCube();
		RCube(int,int);//nXn and size
		void init(int,int);
		void display(GLenum,int);
		void initializeCubes();
		void getBlockPts(float[24][3],int);
		void rotateF(int[],int);
};