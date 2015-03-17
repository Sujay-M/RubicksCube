class Points
{
	GLfloat pt[4];
	public:
		Points(GLfloat ,GLfloat,GLfloat);
		Points operator*(float [4][4]);
		void getPoint(GLfloat[]);
		void setPoint(GLfloat[]);
};