#ifndef MYLIB_H
#define MYLIB_H

#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

#ifdef __cpluscplus
extern "C"{
#endif

void mySolidCylinder(double base, double height, int slices);

void myWireCylinder(double base, double height, int slices);


#ifdef __cpluscplus
}
#endif
#endif  // MYLIB_H

