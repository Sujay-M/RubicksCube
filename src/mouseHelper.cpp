#include "mouseHelper.h"
int checkRevert(int x,int y,State &state)
{
	float initx,inity,px,py;
	int flag=-1;
	initx = -state.SIZE*7.0/4.0;
	inity = state.SIZE;	
	px = (x-state.winW/2)*2*state.w/state.winW;
	py = -(y-state.winH/2)*2*state.w/state.winW;
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
	return flag;
}
float maxZ(float pts[24][3],State &state)
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
int processHT(int hits,unsigned int sb[],int selface,State &state)
{
	GLuint i,*ptr,sel;
	ptr = (GLuint*)sb;
	int final;
	float max = -state.d,pts[24][3];
	for (int i = 0; i < hits; ++i)
	{
		ptr+=3;
		sel = *ptr;
		if(sel<state.no)
		{
			state.c->getBlockPts(pts,sel);
			float curMax = maxZ(pts,state);
			if(max<curMax)
			{
				max = curMax;
				final = sel;
			}
		}
		else
		{
			if(selface==(sel-state.no))
				state.selFace = sel-state.no;
		}
		ptr++;
	}
	return final;
}
int check(int x,int y,State &state)
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
	// glOrtho(-state.SIZE,state.SIZE,-state.SIZE,state.SIZE,-state.SIZE,state.SIZE);
	glOrtho(-state.w,state.w,-state.h*4.0/3.0,state.h*4.0/3.0,-state.d,state.d);
	float mat[16];
	float axis[6][3] = {{-1,0,0},{1,0,0},{0,-1,0},{0,1,0},{0,0,-1},{0,0,1}};
	glGetFloatv(GL_MODELVIEW_MATRIX, mat);
	state.setCur(mat);
	float maxView = 0.0;
	int selectedFace = -1;
	for (int i = 0; i < 6; ++i)
	{	
		Points curAxis;
		curAxis.setPoint(axis[i]);
		curAxis*state.curMat;
		curAxis.getPoint(axis[i]);
		if (axis[i][2]>maxView)
		{
			selectedFace = i;
			maxView = axis[i][2];
		}
		
	}	
	if(selectedFace!=-1)
		state.c->display(GL_SELECT,selectedFace);

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glFlush();
	hits = glRenderMode(GL_RENDER);
	if(hits>0)
		return processHT(hits,sb,selectedFace,state);
	return -1;
}
void getAxis(int dx1,int dy1,float pt[],State &state)
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