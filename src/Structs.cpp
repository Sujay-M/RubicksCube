#include "Structs.h"
State::State(int num) : SIZE(150)
{
	n=num;
	no = (2*n+2*(n-2))*(n-2)+2*n*n;
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			curMat[i][j] = affine[i][j] = 0.0;
	for (int i = 0; i < 4; ++i)
		curMat[i][i] = affine[i][i] = 1.0;
	faceRot = FALSE;
	clicked = FALSE;
	magnitude = 0;
	c.init(n,SIZE);
	w = 320;
	h = 240;
	d = 200;
	winW = 500;
	winH = 500;
	faceCount = 0;
	selectedF = -1;
	dir = 0;
	rotation = FALSE;
	angle = 0;
}
void State::setCur(float *cur)
{
	for (int i = 0,c = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			curMat[j][i] = cur[c++];
}
void State::setCurT(float *cur)
{
	for (int i = 0,c = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			curMat[i][j] = cur[c++];
}