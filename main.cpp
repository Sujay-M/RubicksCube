#include <GL/glut.h>
#include "RubicksCube.hpp"
#include <iostream>
#define SIZE 120
using namespace std;
RCube c(5,SIZE);
void draw()
{
	c.display();
	for(int i=0;i<1000000;i++);
	glRotatef(1.0,1.0,1.0,1.0);
	glutPostRedisplay();
}
void reshape(int w,int h)
{

}
void display()
{
	glClearColor(1,1,1,1);
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	draw();
	glFlush();
}
void myinit()
{

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-100,100,-100,100,-100,100);
	glMatrixMode(GL_MODELVIEW);
}
int main(int argc, char** argv)
{
  	glutInit(&argc, argv);
  	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(300,300);
	glutInitWindowPosition(0,0);
	glutCreateWindow("first");
	myinit();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	// glutIdleFunc(draw);
	glutMainLoop();
	return 0;
}