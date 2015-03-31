#include <GL/glut.h>
#include "Structs.h"
#include <iostream>
#include <cmath>
using namespace std;
State state(3);
float Col[6][3] = {{1,0,0},{0,1,0},{0,0,1},{1,1,0},{1,0,1},{1,1,1}};
char text[] = "RUBICKS CUBE";
void displayFaces(GLenum mode)
{
	float initx ,inity;
	initx = -state.SIZE*7.0/4.0;
	inity = state.SIZE;
	glPushMatrix();
	glRotatef(90,0,1,0);
	glTranslatef(0,inity,initx);
	glScalef(0.5,0.5,0.5);		
	state.c.display(mode,0);
	inity-=state.SIZE;
	glLoadIdentity();
	glRotatef(180,0,1,0);
	glTranslatef(-initx,inity,0);
	glScalef(0.5,0.5,0.5);
	state.c.display(mode,4);
	inity-=state.SIZE;
	glLoadIdentity();
	glRotatef(-90,0,1,0);
	glTranslatef(0,inity,-initx);
	glScalef(0.5,0.5,0.5);		
	state.c.display(mode,1);
	initx = state.SIZE*7.0/4.0;
	inity = state.SIZE;
	glLoadIdentity();
	glRotatef(90,1,0,0);
	glTranslatef(initx,0,-inity);
	glScalef(0.5,0.5,0.5);		
	state.c.display(mode,3);
	inity -= state.SIZE;
	glLoadIdentity();
	glTranslatef(initx,inity,0);
	glScalef(0.5,0.5,0.5);		
	state.c.display(mode,5);
	inity -= state.SIZE;
	glLoadIdentity();
	glRotatef(-90,1,0,0);
	glTranslatef(initx,0,inity);
	glScalef(0.5,0.5,0.5);		
	state.c.display(mode,2);
	glPopMatrix();

}
void checkRevert(int x,int y)
{
	float initx,inity,px,py;
	int flag=-1;
	initx = -state.SIZE*7.0/4.0;
	inity = state.SIZE;	
	px = (x-state.winW/2)*2*state.w/state.winW;
	py = -(y-state.winH/2)*2*state.h/state.winH;
	if(px>(initx-state.SIZE/2)&& px<(initx+state.SIZE/2))
		for (int i = 0; i < 3; ++i)
		{
			if(py>(inity-state.SIZE/2)&& py<(inity+state.SIZE/2))
			{
				flag = i;
				break;
			}
			inity-=state.SIZE;
		}
	initx = state.SIZE*7.0/4.0;
	inity = state.SIZE;
	if(px>(initx-state.SIZE/2)&& px<(initx+state.SIZE/2))
		for (int i = 0; i < 3; ++i)
		{
			if(py>(inity-state.SIZE/2)&& py<(inity+state.SIZE/2))
			{
				flag = i+3;
				break;
			}
			inity-=state.SIZE;
		}
	if(flag!=-1)
	{
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		switch(flag)
		{
			case 0:glRotatef(90,0,1,0);break;
			case 1:glRotatef(180,0,1,0);break;
			case 2:glRotatef(-90,0,1,0);break;
			case 3:glRotatef(90,1,0,0);break;
			case 4:break;
			case 5:glRotatef(-90,1,0,0);break;
		}
	}
}
void displayText()
{
	for (int i = 0; i < 12; ++i)
	{
		glColor3fv(Col[i/2]);
		glRasterPos3i(-state.SIZE+i*24,state.SIZE,state.d);
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,text[i]);
	}

}
float maxZ(float pts[24][3])
{
	float max = -state.d;
	float mat[16];
	Points temp;
	glGetFloatv(GL_MODELVIEW_MATRIX, mat);
	state.setCur(mat);
	for (int i = 0; i < 24; ++i)
	{
		temp.setPoint(pts[i]);
		temp*state.curMat;
		temp.getPoint(pts[i]);
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
	float max = -state.d,pts[24][3];
	for (int i = 0; i < hits; ++i)
	{
		ptr+=3;
		sel[i] = *ptr;
		state.c.getBlockPts(pts,sel[i]);
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
	glSelectBuffer(state.SIZE,sb);
	glRenderMode(GL_SELECT);
	glInitNames();
	glPushName(0);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluPickMatrix((double)x,(double)(vp[3]-y),1,1,vp);
	glOrtho(-state.w,state.w,-state.h,state.h,-state.d,state.d);
	state.c.display(GL_SELECT,-1);
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glFlush();
	hits = glRenderMode(GL_RENDER);
	if(hits>0)
		return processHT(hits,sb);
	return -1;
}
void getAxis(int dx1,int dy1,float pt[])
{
	if(dy1==0 && dx1>0)
	{
		pt[0] = 0;
		pt[1] = 1;
		pt[2] = 0;
	}
	else if(dy1==0 && dx1<0)
	{
		pt[0] = 0;
		pt[1] = -1;
		pt[2] = 0;
	}
	else if(dy1<0 && dx1<=0)
	{
		pt[0] = -1;
		pt[1] = -(dx1)/(float)(dy1);
		pt[2] = 0;
	}
	else if(dy1<0 && dx1>0)
	{
		pt[0] = -1;
		pt[1] = -(dx1)/(float)(dy1);
		pt[2] = 0;
	}
	else if(dy1>0 && dx1<=0)
	{
		pt[0] = 1;
		pt[1] = (dx1)/(float)(dy1);
		pt[2] = 0;
	}
	else if(dy1>0 && dx1>0)
	{
		pt[0] = 1;
		pt[1] = (dx1)/(float)(dy1);
		pt[2] = 0;
	}
}
int faceInfo(int x,int y)
{
	float pts[24][3];
	Points temp;
	float mat[16],px,py;
	glGetFloatv(GL_MODELVIEW_MATRIX, mat);
	state.setCur(mat);
	int face=-1;
	state.dummy.getPoints(pts);
	float max = -200;
	px = (x-state.winW/2)*2*state.w/state.winW;
	py = -(y-state.winH/2)*2*state.h/state.winH;
	for (int i = 0, count=0; i < 6; ++i)
	{
		float xmax=-state.w,xmin = state.w,ymax = -state.h,ymin = state.h,zmax = -state.d;
		for(int j =0 ;j<4;j++)
		{	
			cout<<"i = "<<i<<endl;
			temp.setPoint(pts[count]);
			cout<<temp;
			temp*state.curMat;
			temp.getPoint(pts[count]);
			if(xmax < pts[count][0])
				xmax = pts[count][0];
			if(xmin > pts[count][0])
				xmin = pts[count][0];
			if(ymax < pts[count][1])
				ymax = pts[count][1];
			if(ymin > pts[count][1])
				ymin = pts[count][1];
			if(zmax < pts[count][2])
				zmax = pts[count++][2];
		}
		cout<<"x = "<<px<<"y = "<<py<<" xmin,xmax "<<xmin<<","<<xmax<<" ymin,ymax "<<ymin<<","<<ymax<<" z = "<<zmax<<endl;
		if(px<xmax && px>xmin && py<ymax && py>ymin && zmax>max)
		{
			// cout<<"hi"<<endl;
			face = i;
			max = zmax;
		}
	}
	return face;
}
void mouse(int btn,int st,int x,int y)
{
	int block;
	int cy = 500-y;
	if(btn == GLUT_LEFT_BUTTON && st == GLUT_DOWN)
	{
		checkRevert(x,y);
		state.clicked = TRUE;
		state.xp = x;
		state.yp = cy;
		state.index = 0;
		if((block = check(x,y))!=-1)
		{
			state.selBlocks[state.index++] = block;
			state.faceRot = TRUE;		
		}	
		else
			state.faceRot = FALSE;
	}
	if(btn == GLUT_LEFT_BUTTON && st == GLUT_UP )
	{
		float lx = (x - 250)/500.0*400.0;
		float ly = (cy - 250)/500.0*400.0;
		state.clicked = FALSE;
		if(state.faceRot==TRUE)	
			state.c.rotateF(state.selBlocks,state.index);
				
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
			getAxis(x - state.xp,state.yp - cy,pt);
			state.axis.setPoint(pt);
			state.magnitude = sqrt((x-state.xp)*(x-state.xp)+(cy-state.yp)*(cy-state.yp));
		}
		else
		{
			block = check(x,y);
			if(block != state.selBlocks[state.index-1])
			{
				state.selBlocks[state.index++] = block;
				int face = faceInfo(x,y);
				cout<<"face = "<<face<<endl;
			}
		}	
		state.xp = x;
		state.yp = cy;
	}
}

void draw()
{
	int *disp = new int[state.no];float pt[3];
	float mat[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, mat);
	state.setCurT(mat);
	state.axis*state.curMat;
	state.axis.getPoint(pt);
	state.c.display(GL_RENDER,-1);
	glPushMatrix();
	glLoadIdentity();
	displayText();
	displayFaces(GL_RENDER);
	glPopMatrix();
	glRotatef(state.magnitude,pt[0],pt[1],pt[2]);
	state.magnitude = 0;
	glutPostRedisplay();
	delete(disp);
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
	glOrtho(-state.w,state.w,-state.h*4.0/3.0,state.h*4.0/3.0,-state.d,state.d);
	glMatrixMode(GL_MODELVIEW);
}
void display()
{
	glMatrixMode(GL_MODELVIEW);
	glClearColor(0,0,0,1);
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	draw();
	glFlush();
}
int main(int argc, char** argv)
{
  	glutInit(&argc, argv);
  	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(state.winW,state.winH);
	glutInitWindowPosition(0,0);
	glutCreateWindow("RUBICKS CUBE");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutMainLoop();
	return 0;
}