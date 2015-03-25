#include <GL/glut.h>
#include "Cube.hpp"
class RCube
{
	int n,size,***cubeBlockNo;
	Cube *blocks;
	
	public:
		RCube();
		RCube(int,int);//nXn and size
		void init(int,int);
		void rotateFace(int,int);
		void display(GLenum);
		void initializeCubes();
		void getBlockPts(float[24][3],int);
		void rotateCube(float[4][4]);
};
