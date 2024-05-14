#include <stdlib.h>
#include <GL/glut.h>
#include "CFinger.h"
#include "mylib.h"

CFinger::CFinger()
{
	static float	amb[4]={253./255., 198./255., 146./255., 1.0};
	static float	dif[4]={0.3, 0.3, 0.3, 1.0};
	static float	spe[4]={0.2, 0.2, 0.2, 1.0};
	
	for (int i = 0 ; i < 4 ; i++ ){
		ambient[i] = amb[i];
		diffuse[i] = dif[i];
		specular[i] = spe[i];
	}
	shininess = 128.0;

}

void CFinger::set(double x0, double y0, double z0, double zang0,
								double len[], double rad[], int ang[])
{
	x = x0;
	y = y0;
	z = z0;
	zangle = zang0;
	for (int i = 0 ; i <= 2 ; i++ ){
		length[i] = len[i];
		radius[i] = rad[i];
		angle [i] = ang[i];
	}
}

void CFinger::rotateAngle(int mode, int fngNo, int ang)
{
	if ( fngNo < 0 || fngNo > 2 ) exit (0);
	switch (mode){
		case 1:		// relative angle
			angle[fngNo] = (angle[fngNo] + ang) % 360;
			break;
		case 2:		// absolute angle
			angle[fngNo] = ang;
			break;
		default:
			exit (0);
	}
}

void CFinger::draw()
{
	int	slices = 10, ss = 18;

	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialf (GL_FRONT, GL_SHININESS, shininess);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glPushMatrix();

	glTranslated(x, y, z);					// move to the origin
	glRotated(zangle, 0.0, 0.0, 1.0);

/* First bone ; äÓêﬂçú */
	glutSolidSphere(radius[0], ss, ss);
	glRotated((double)angle[0], 1.0, 0.0, 0.0);
	glTranslated(0.0, length[0]/2.0, 0.0);
	mySolidCylinder(radius[0], length[0], slices);
	glTranslated(0.0, length[0]/2.0, 0.0);
	glutSolidSphere(radius[0], ss, ss);
/* Second bone ; íÜêﬂçú */
	glRotated((double)angle[1], 1.0, 0.0, 0.0);
	glTranslated(0.0, length[1]/2.0, 0.0);
	mySolidCylinder(radius[1], length[1], slices);
	glTranslated(0.0, length[1]/2.0, 0.0);
	glutSolidSphere(radius[1], ss, ss);
/* Third bone ;  ññêﬂçú */
	glRotated((double)angle[2], 1.0, 0.0, 0.0);
	glTranslated(0.0, length[2]/2.0, 0.0);
	mySolidCylinder(radius[2], length[2], slices);
/* Finger tip */
	glTranslated(0.0, length[2]/2.0, 0.0);
	glutSolidSphere(radius[2]*0.9, ss, ss);

	glPopMatrix();
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
}
