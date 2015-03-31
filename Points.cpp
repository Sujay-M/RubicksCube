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
Points Points::operator*(Points p2)
{
	GLfloat pts[3],res[3];
	p2.getPoint(pts);
	Points p3;
	res[0] = pt[1]*pts[2] - pts[1]*pt[2];
	res[1] = pt[2]*pts[0] - pts[2]*pt[0];
	res[2] = pt[0]*pts[1] - pts[0]*pt[1];
	p3.setPoint(res);
	return p3;
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