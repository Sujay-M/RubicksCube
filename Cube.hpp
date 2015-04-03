#include <GL/glut.h>
#include "Points.hpp"
class Cube
{
	Points face[6][4];
	Points latticePts[8];
	GLfloat color[6][3];
	bool dispFace[6];
	public:
		Cube();
		Cube(GLfloat[],int);
		void setColor(int,GLfloat[]);
		void getColor(int,GLfloat[]);
		void initialize(GLfloat[],int);
		void setLattice(GLfloat[],int);
		void initFromLattice();
		void render(GLenum,int);
		void drawOutLine(GLenum,int,bool numberFace=FALSE);
		void getPoints(float[24][3]);
		void rotate(float[4][4]);
};