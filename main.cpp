#include <GL/glut.h>
#include "RubicksCube.hpp"
#include <iostream>
#include <cstdlib>
#include <cmath>
#define SIZE 150
using namespace std;
int xp,yp;
bool clicked = FALSE;
bool faceRot = FALSE;
float state[3][3] = {{0,90.0,90.0},{90.0,0.0,90.0},{90.0,90.0,0.0}};
int index,selBlocks[100];
RCube c(3,SIZE);
float maxZ(float pts[24][3])
{
	float max = -200;
	for (int i = 0; i < 24; ++i)
	{
		if(pts[i][2]>max)
			max = pts[i][2];
	}
	return max;
}
int processHT(int hits,unsigned int sb[])
{
	GLuint i,*ptr,sel[100];
	ptr = (GLuint*)sb;
	int final;
	float max = -200,pts[24][3];
	for (int i = 0; i < hits; ++i)
	{
		ptr+=3;
		sel[i] = *ptr;
		c.getBlockPts(pts,sel[i]);
		float curMax = maxZ(pts);
		if(max<curMax)
		{
			max = curMax;
			final = sel[i];
		}
		ptr++;
	}
	return final;
}
int check(int x,int y)
{
	unsigned int sb[100];
	int hits,vp[4];
	glGetIntegerv(GL_VIEWPORT,vp);
	glSelectBuffer(SIZE,sb);
	glRenderMode(GL_SELECT);
	glInitNames();
	glPushName(0);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluPickMatrix((double)x,(double)(vp[3]-y),1,1,vp);
	glOrtho(-200,200,-200,200,-200,200);
	c.display(GL_SELECT);
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glFlush();
	hits = glRenderMode(GL_RENDER);
	// cout<<"hits = "<<hits<<endl;
	if(hits>0)
		return processHT(hits,sb);
	return -1;
}
void rotMatrix(int theta,int axis,float affine[4][4])
{
	float rad = theta*(3.14/180.0);
	float s,c;
	s = sin(rad);
	c = cos(rad);
	if(axis==0)
	{
		float temp[4][4] = {{1.0,0,0,0},{0,c,-s,0},{0,s,c,0},{0,0,0,1.0}};
		for(int i=0;i<4;i++)
			for(int j=0;j<4;j++)
				affine[i][j] = temp[i][j];
	}
	else if(axis==1)
	{
		float temp[4][4] = {{c,0,s,0},{0,1.0,0,0},{-s,0,c,0},{0,0,0,1.0}};
		for(int i=0;i<4;i++)
			for(int j=0;j<4;j++)
				affine[i][j] = temp[i][j];
	}
	else if(axis==2)
	{
		float temp[4][4] = {{c,-s,0,0},{s,c,0,0},{0,0,1.0,0},{0,0,0,1.0}};
		for(int i=0;i<4;i++)
			for(int j=0;j<4;j++)
				affine[i][j] = temp[i][j];
	}
}
void rotateView(int w,int h)
{
	float theta,xth,yth,zth;
	float affine[4][4];
	theta = (w/500.0)*60;
	rotMatrix(theta,1,affine);
	c.rotateCube(affine);
	theta = (h/500.0)*60;
	rotMatrix(theta,0,affine);
	c.rotateCube(affine);
	glutPostRedisplay();
}

void draw()
{
	c.display(GL_SELECT);
	// for(int i=0;i<1000000;i++);
	// glRotatef(10.0,1.0,1.0,1.0);
	// glutPostRedisplay();
}
void reshape(int w,int h)
{
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(w>=h)
		glOrtho(-200*(float)w/(float)h,200*(float)w/(float)h,-200,200,-200,200);
	else
		glOrtho(-200,200,-200*(float)h/(float)w,200*(float)h/(float)w,-200,200);
	glMatrixMode(GL_MODELVIEW);
}
void display()
{
	glClearColor(0,0,0,1);
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	draw();
	glFlush();
}
void mouse(int btn,int state,int x,int y)
{
	int block;
	if(btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		clicked = TRUE;
		xp = x;
		yp = y;
		index = 0;
		if((block = check(x,y))!=-1)
		{
			selBlocks[index++] = block;
			faceRot = TRUE;		
		}	
		else
			faceRot = FALSE;
	}
	if(btn == GLUT_LEFT_BUTTON && state == GLUT_UP )
	{
		clicked = FALSE;
		if(faceRot==FALSE)
			rotateView((x-xp),(y-yp));
		else
		{
			cout<<" selBlocks "<<endl;
			for (int i = 0; i < index; ++i)
			{
				cout<<selBlocks[i]<<endl;
			}
		}
	}


}
void motion(int x,int y)
{
	if(clicked==TRUE)
	{
		if(faceRot==FALSE)
			rotateView((x-xp),(y-yp));
		else
			selBlocks[index++] = check(x,y);
		xp = x;
		yp = y;
	}
}
void myinit()
{

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-200,200,-200,200,-200,200);
	glMatrixMode(GL_MODELVIEW);
}
int main(int argc, char** argv)
{
  	glutInit(&argc, argv);
  	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);
	glutCreateWindow("first");
	myinit();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	// glutIdleFunc(draw);
	glutMainLoop();
	return 0;
}