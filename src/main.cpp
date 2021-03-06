#include <cstdlib>
#include <ctime>
#include <GL/glut.h>
#include "Structs.h"
#include "mouseHelper.h"
#include "displayHelper.h"
#include <iostream>
#include <cmath>
using namespace std;
State state;
int MROTS = 3;
void mouse(int btn,int st,int x,int y)
{
	int block;
	int cy = 500-y;
	if(btn == GLUT_LEFT_BUTTON && st == GLUT_DOWN)
	{
		if(checkRevert(x,y,state)==-1)
		{
			state.clicked = TRUE;
			state.xp = x;
			state.yp = cy;
			state.dir = 0;
			state.index = 0;
			if((block = check(x,y,state))!=-1)
			{
				state.selBlocks[state.index++] = block;
				state.faceRot = TRUE;
				float px = (x-state.winW/2)*2*state.w/state.winW;
				float py = -(y-state.winH/2)*2*state.w/state.winW;
			}	
			else
				state.faceRot = FALSE;
		}
	}
	if(btn == GLUT_LEFT_BUTTON && st == GLUT_UP )
	{
		state.clicked = FALSE;
		if(state.faceRot == TRUE)
		{
			int face,clk;
			state.faceRot = FALSE;
			clk = state.c->initRotateFace(state.selBlocks,state.index,state.selFace,state.selectedF);
			if(state.selectedF!=-1&&clk!=-1)
			{
				// animate(state.selectedF,clk,state)
				state.dir = clk;
				state.rotation = TRUE;
				state.angle = 0;
			}
		}
	}
}
void motion(int x,int y)
{
	int cy = 500-y;
	int block;
	float pt[3];
	if(state.clicked==TRUE)
	{
		if(state.faceRot==FALSE)
		{
			getAxis(x - state.xp,state.yp - cy,pt,state);
			state.axis.setPoint(pt);
			state.magnitude = sqrt((x-state.xp)*(x-state.xp)+(cy-state.yp)*(cy-state.yp));
		}
		else
		{
			block = check(x,y,state);
			if(state.selBlocks[state.index-1]!=block)
				state.selBlocks[state.index++] = block;
		}	
		state.xp = x;
		state.yp = cy;
	}
}


void reshape(int w,int h)
{
	state.winW = w;
	state.winH = h;
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(w>=h)
		state.w = 320*(float)w/(float)h;
	else
		state.h = 240*(float)h/(float)w;
	// glOrtho(-state.SIZE,state.SIZE,-state.SIZE,state.SIZE,-state.SIZE,state.SIZE);
	glOrtho(-state.w,state.w,-state.h*4.0/3.0,state.h*4.0/3.0,-state.d,state.d);
	glMatrixMode(GL_MODELVIEW);
}
void display()
{
	glMatrixMode(GL_MODELVIEW);
	glClearColor(0,0,0,1);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_LOGIC_OP);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	if(state.start==TRUE)
	{
		if(state.rotation==FALSE)
		{
			state.rotation = TRUE;
			state.angle = 0;
			state.selectedF = rand()%(3*state.n);
			state.dir = rand()%2;
			state.count++;
		}
		if(state.count==MROTS)
		{
			state.start = FALSE;
			state.count = 0;
		}
	}
	
	draw(state);
	glFlush();
}
void key(unsigned char ch,int x,int y)
{
	if(state.win)
		switch(ch)
		{
			case 'y':
				state.start = TRUE;
				break;
			case 'n':
				exit(0);
		}
}
int main(int argc, char** argv)
{
	int n;
	cout<<"enter n"<<endl;
	cin>>n;
	state.init(n); 
	srand(time(0));
  	glutInit(&argc, argv);
  	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(state.winW,state.winH);
	glutInitWindowPosition(0,0);
	glutCreateWindow("RUBICKS CUBE");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutKeyboardFunc(key);
	glutMainLoop();
	return 0;
}