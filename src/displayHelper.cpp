#include "displayHelper.h"
float Col[6][3] = {{1,0,0},{0,1,0},{0,0,1},{1,1,0},{1,0,1},{1,1,1}};
char text[] = "RUBICKS CUBE";
void displayFaces(GLenum mode,State &state)
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
void displayText(State &state)
{
	for (int i = 0; i < 12; ++i)
	{
		glColor3fv(Col[i/2]);
		glRasterPos3i(-state.SIZE+i*24,state.SIZE,state.d);
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,text[i]);
	}

}
void animate(State &state)
{
	float mat[16];
	state.dir = (state.dir==1)?1:-1;
	float axis[6][3] = {{1,0,0},{-1,0,0},{0,1,0},{0,-1,0},{0,0,1},{0,0,-1}};
	glGetFloatv(GL_MODELVIEW_MATRIX, mat);
	glPushMatrix();
	Points temp;
	float tempAxis[3];
	temp.setPoint(axis[state.selectedF]);
	state.setCur(mat);
	temp*state.curMat;
	temp.getPoint(tempAxis);	
	glLoadIdentity();
	glRotatef(state.angle,state.dir*tempAxis[0],state.dir*tempAxis[1],state.dir*tempAxis[2]);
	glMultMatrixf(mat);
	state.c.display(GL_RENDER,state.selectedF);
	glPopMatrix();
	state.angle++;
	if(state.angle==90)
	{
		state.rotation = FALSE;
		state.dir = (state.dir==1)?1:0;
		state.c.rotateFace(state.selectedF,state.dir);
	}
	
}
void draw(State &state)
{
	int *disp = new int[state.no];float pt[3];
	float mat[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, mat);
	state.setCurT(mat);
	state.axis*state.curMat;
	state.axis.getPoint(pt);
	if(state.rotation==TRUE)
	{	
		animate(state);
		state.c.display(GL_RENDER,state.selectedF,0);
	}
	else
		state.c.display(GL_RENDER,-1);
	glPushMatrix();
	glLoadIdentity();
	displayText(state);
	displayFaces(GL_RENDER,state);
	glPopMatrix();
	glRotatef(state.magnitude,pt[0],pt[1],pt[2]);
	state.magnitude = 0;
	glutPostRedisplay();
	delete(disp);
}