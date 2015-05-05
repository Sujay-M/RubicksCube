#ifndef _STRUCTS
#define _STRUCTS
#include "RCube.hpp"
struct State
{
	bool clicked,faceRot,rotation,start;
	const int SIZE;
	int selBlocks[100],index,selFace,selectedF,n,no,xp,yp,magnitude,w,h,d,winW,winH,dir,angle,speed,win,count;
	float affine[4][4],curMat[4][4];
	RCube *c;
	Points axis;
	State();
	void setCur(float*);
	void setCurT(float*);
	void init(int);
};
#endif