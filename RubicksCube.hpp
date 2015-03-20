#include <GL/glut.h>
#include "Cube.hpp"
class RCube
{
	int n,size,*faceBlocks[6];
	Cube *blocks;
	
	public:
		RCube();
		RCube(int,int);//nXn and size
		void init(int,int);
		void rotateFace(int,int);
		void display();
		void initializeCubes();
		void rotateCube(float[4][4]);
};
