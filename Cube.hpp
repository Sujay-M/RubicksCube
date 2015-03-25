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
		void initialize(GLfloat[],int);
		void setLattice(GLfloat[],int);
		void initFromLattice();
		void render(GLenum,int);
		void rotate(float[4][4]);
		void displayPoints();
		void displayColor();
		void getPoints(float[24][3]);
};