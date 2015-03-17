#include "Points.hpp"
class Cube
{
	Points face[6][4];
	GLfloat color[6][3];
	bool dispFace[6];
	public:
		void Cube();
		void Cube(GLfloat[],int,GLfloat[][3]);
		void initialize(GLfloat[],int,GLfloat[][3]);
		void render();
}