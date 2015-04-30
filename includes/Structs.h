#ifndef _STRUCTS
#define _STRUCTS
#include "RCube.hpp"
struct State
{
	bool clicked,faceRot,rotation;
	const int SIZE;
	int selBlocks[100],index,selFaces[10],selectedF,faceCount,n,no,xp,yp,magnitude,w,h,d,winW,winH,dir,angle;
	float affine[4][4],curMat[4][4];
	RCube c;
	Points axis;
	State(int);
	void setCur(float*);
	void setCurT(float*);
};
#endif