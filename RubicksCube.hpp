#include "Cube.hpp"
class RCube
{
	int n,size,*faceBlocks[6];
	Cube *blocks;
	static GLfloat Color[6][3] = {{1,0,0},{0,1,0},{0,0,1},{1,1,0},{1,0,1},{1,1,1}};
	public:
		RCube(int,int);//nXn and size
		void rotateFace(int,int);
		void display();
		void initializeCubes();

}