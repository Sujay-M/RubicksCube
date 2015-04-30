#ifndef _RCUBE
#define _RCUBE
#include <GL/glut.h>
#include "Cube.hpp"
class RCube
{
	int n,size,***cubeBlockNo,*faceBlocks[6];
	Cube *blocks,outLine;
	
	public:
		RCube();
		RCube(int,int);//nXn and size
		void init(int,int);
		void display(GLenum,int,int flag = 1);
		void initializeCubes();
		void getBlockPts(float[24][3],int);
		int initRotateFace(int[],int,int[],int,int&);
		void rotateFace(int,bool);
};
#endif