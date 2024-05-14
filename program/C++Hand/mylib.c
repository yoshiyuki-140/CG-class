#include "mylib.h"

void mySolidCylinder(double base, double height, int slices)
/****************************************************************************
 * base		The radius of the base of the cylinder.
 * height	The height of the cylinder.
 * slices	The number of subdivisions around the Z axis.
 ****************************************************************************/
{
#include <math.h>
#ifndef M_TWOPI
#define M_TWOPI (2*M_PI)
#endif

	double x, y, z, dq;
	int i;

	glEnable(GL_NORMALIZE);
    dq = M_TWOPI/(double)slices;
	y = 0.5*height;
	glPushMatrix();
	glRotated(-dq*180.0/M_TWOPI, 0.0, 0.1, 0.0);
    glBegin(GL_QUAD_STRIP);
    for (i = 0; i <= slices; i += 1){
		x = base*cos( dq*(double)i );
		z = base*sin( dq*(double)i );
		glNormal3d(x,  0, z);
		glVertex3d(x,  y, z);
		glVertex3d(x, -y, z);
    }
    glEnd();
    glBegin(GL_POLYGON);
	glNormal3d(0.0, -1.0, 0.0);
   	for (i = 0; i < slices; i+=1){
		x = base*cos(dq*(double)i );
		z = base*sin(dq*(double)i );
		glVertex3d(x, -y, z);
    }
    glEnd();
    glBegin(GL_POLYGON);
	glNormal3d(0.0, 1.0, 0.0);
    for (i = 0; i < slices; i+=1){
		x = base*cos(dq*(double)i);
		z = base*sin(dq*(double)i);
		glVertex3d(x, y, z);
    }
    glEnd();
	glPopMatrix();
    glDisable(GL_NORMALIZE);
}

void myWireCylinder(double base, double height, int slices)
/****************************************************************************
 * base		The radius of the base of the cylinder.
 * height	The height of the cylinder.
 * slices	The number of subdivisions around the Z axis.
 ****************************************************************************/
{
    double x, y, z, dq;
	int i;

    dq = M_TWOPI/(double)slices;
	y = 0.5*height;
	glPushMatrix();
	glRotated(-dq*180.0/M_TWOPI, 0.0, 1.0, 0.0);
    glBegin(GL_LINES);
    for (i = 0; i < slices; i++){
		x = base*cos(dq*(double)i);
		z = base*sin(dq*(double)i);
		glVertex3d(x,  y, z);
		glVertex3d(x, -y, z);
	}
    glEnd();

    glBegin(GL_LINE_LOOP);
	for (i = 0; i < slices; i++){
		x = base*cos(dq*(double)i);
		z = base*sin(dq*(double)i);
		glVertex3d(x, y, z);
	}
	glEnd();

    glBegin(GL_LINE_LOOP);
	for (i = 0; i < slices; i++){
		x = base*cos(dq*(double)i);
		z = base*sin(dq*(double)i);
		glVertex3d(x, -y, z);
	}
	glEnd();
	glPopMatrix();
}
