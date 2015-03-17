#include <GL/glut.h>
# include <iostream>
using namespace std;
class Points
{
	GLfloat pt[4];
	public:
		Points();
		Points(GLfloat ,GLfloat,GLfloat);
		Points operator*(float [4][4]);
		friend ostream &operator<<(ostream &stream, Points p);
		void getPoint(GLfloat[]);
		void setPoint(GLfloat[]);
};