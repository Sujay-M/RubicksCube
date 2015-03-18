#include <GL/glut.h>
#include "Points.hpp"
class Cube
{
	Points face[6][4];
	GLfloat color[6][3];
	bool dispFace[6];
	public:
		Cube();
		Cube(GLfloat[],int);
		void setColor(int,GLfloat[]);
		void initialize(GLfloat[],int);
		void render();
		void displayPoints();
		void displayColor();
};