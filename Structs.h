#ifndef _STRUCTS
#define _STRUCTS
#include "RCube.hpp"
struct State
{
	bool clicked,faceRot;
	const int SIZE;
	int index,selBlocks[100],n,no,xp,yp,magnitude,w,h,d,winW,winH;
	float affine[4][4],curMat[4][4];
	RCube c;
	Cube dummy;
	Points axis;
	State(int);
	void setCur(float*);
	void setCurT(float*);
};
#endif