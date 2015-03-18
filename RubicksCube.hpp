#include <GL/glut.h>
#include "Cube.hpp"
class RCube
{
	int n,size,*faceBlocks[6];
	Cube *blocks;
	
	public:
		RCube(int,int);//nXn and size
		void rotateFace(int,int);
		void display();
		void initializeCubes();
};
