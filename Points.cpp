#include "Points.hpp"
# include <iostream>
using namespace std;
Points::Points()
{
	pt[0] = 0.0;
	pt[1] = 0.0;
	pt[2] = 0.0;
	pt[3] = 1.0;
}
Points::Points(GLfloat x1,GLfloat y1,GLfloat z1)
{
	pt[0] = x1;
	pt[1] = y1;
	pt[2] = z1;
	pt[3] = 1.0;
}
Points Points::operator*(float affine[4][4])
{
	GLfloat result[] = {0.0,0.0,0.0,0.0};
	for(int j=0;j<4;j++)
		for(int i=0;i<4;i++)
			result[j]+= affine[j][i]*pt[i]; 
	for(int i=0;i<4;i++)
		pt[i] = result[i];
	return *this;
}
void Points::getPoint(GLfloat ptbuf[])
{
	for(int i=0;i<3;i++)
		ptbuf[i] = pt[i];
}
void Points::setPoint(GLfloat ptbuf[])
{
	for(int i=0;i<3;i++)
		pt[i] = ptbuf[i];
	pt[4] = 1.0;
}
ostream &operator<<(ostream &stream, Points p)
{
	GLfloat pt[3];
	p.getPoint(pt);
	stream << "x = "<<pt[0]<<" y = "<<pt[1]<<" z = "<<pt[2]<<endl ;
	return stream;
}