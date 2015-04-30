#ifndef _MOUSEHELPER
#define _MOUSEHELPER
#include <GL/glut.h>
#include "Structs.h"
#include "displayHelper.h"
void checkRevert(int,int,State&);
float maxZ(float[24][3],State&);
int processHT(int,unsigned int[],State&);
int check(int,int,State&);
void getAxis(int,int,float[],State&);
#endif