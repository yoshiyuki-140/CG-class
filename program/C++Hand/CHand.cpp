#include "CFinger.h"
#include "CHand.h"
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

CHand::CHand()
{
	int	i,j;
/*---------------------------------------------------------------------------
 * Set up the vertex of the hand palm
 *---------------------------------------------------------------------------*/
	double	p[][Hand_Points_XYZ]={{0,0,0},{6,0,0},{8,5,0},{6,7,0},
							{5,9.8,0},{2.5,10,0},{0,10,0},{-2,9,0},{-3,7,0}};

	for (i = 0 ; i < Hand_Points ; i++){
		for (j = 0 ; j < Hand_Points_XYZ ; j++){
			pnt[i][j] = p[i][j];
		}
	}
	thickness = 3.0;		// thickness of the palm
/*---------------------------------------------------------------------------
 * Set up the fingers.
 * len[][] and rad[][] are length and radius of each finger, respectively.
 * fb[5][3] represents the bases of the fingers
 * fb[i][3], i = 0 - 4 means the finger number; thumb to pinkie
 * The 3 above means x, y-coordinates and angle around z-axis
 * under the condition the hand CG draws on xy-plane.		
 *---------------------------------------------------------------------------*/
	double	len[5][3]={{4.0, 0.1, 3.0}, {5.0, 3.0, 2.0}, {5.2, 3.2, 2.2},
					   {5.0, 3.0, 2.0}, {3.0, 2.0, 2.0}};
	double	rad[5][3]={{1.2, 1.0, 1.0}, {1.0, 0.9, 0.9}, {1.0, 0.9, 0.9},
					   {1.0, 0.9, 0.9}, {0.9, 0.8, 0.8}};
	int		ang[]={0, 0, 0};
	double	fb[5][3];
/*---------------------------------------------------------------------------
 * Calculate the (x,y) and theta_z of the base of finger
 *---------------------------------------------------------------------------*/
	/* 0nd finger base */
	fb[0][0] = (pnt[2][0] + pnt[3][0])/2;
	fb[0][1] = (pnt[2][1] + pnt[3][1])/2;
	fb[0][2] = atan((pnt[2][1] - pnt[3][1])/(pnt[2][0] - pnt[3][0]))*180/M_PI;
	/* 1st finger base */
	fb[1][0] = (pnt[4][0] + pnt[5][0])/2;
	fb[1][1] = (pnt[4][1] + pnt[5][1])/2;
	fb[1][2] = atan((pnt[4][1] - pnt[5][1])/(pnt[4][0] - pnt[5][0]))*180/M_PI;
	/* 2nd finger base */
	fb[2][0] = (pnt[5][0] + pnt[6][0])/2;
	fb[2][1] = (pnt[5][1] + pnt[6][1])/2;
	fb[2][2] = atan((pnt[5][1] - pnt[6][1])/(pnt[5][0] - pnt[6][0]))*180/M_PI;
	/* 3rd finger base */
	fb[3][0] = (pnt[6][0] + pnt[7][0])/2;
	fb[3][1] = (pnt[6][1] + pnt[7][1])/2;
	fb[3][2] = atan((pnt[6][1] - pnt[7][1])/(pnt[6][0] - pnt[7][0]))*180/M_PI;
	fb[3][2] -= 20.0;
	/* 4th finger base */
	fb[4][0] = (pnt[7][0] + pnt[8][0])/2;
	fb[4][1] = (pnt[7][1] + pnt[8][1])/2;
	fb[4][2] = atan((pnt[7][1] - pnt[8][1])/(pnt[7][0] - pnt[8][0]))*180/M_PI;
	fb[4][2] -= 35.0;

	for(i = 0; i < 5; i++){
		finger[i] = new CFinger();
		finger[i]->set(fb[i][0], fb[i][1], 0.0, fb[i][2], len[i], rad[i], ang);
	}
}

void CHand::draw()
{
	int	i;
	double	z0 = thickness/2.0;

	static float	amb1[4]={253./255., 200./255., 156./255., 1.0};
	static float	dif1[4]={0.3, 0.3, 0.3, 1.0};
	static float	spe1[4]={0.2, 0.2, 0.2, 1.0};

	static float	amb2[4]={217./255., 156./255., 128./255., 1.0};
	static float	dif2[4]={0.3, 0.3, 0.3, 1.0};
	static float	spe2[4]={0.2, 0.2, 0.2, 1.0};

	static float	amb3[4]={253./255., 198./255., 146./255., 1.0};
	static float	dif3[4]={0.2, 0.2, 0.2, 1.0};
	static float	spe3[4]={0.1, 0.1, 0.1, 1.0};

	//palm of hand
	glMaterialfv(GL_FRONT, GL_AMBIENT, amb1);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, dif1);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe1);
	glMaterialf (GL_FRONT, GL_SHININESS, 128.);

	glBegin(GL_TRIANGLE_FAN); 
		for (i = 0 ; i < Hand_Points ; i++){
			glVertex3d(pnt[i][0], pnt[i][1], z0);
		}
	glEnd();

	//back of hand
	glMaterialfv(GL_FRONT, GL_AMBIENT, amb2);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, dif2);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe2);
	glMaterialf (GL_FRONT, GL_SHININESS, 64.);

	glBegin(GL_TRIANGLE_FAN); 
		for (i = 0 ; i < Hand_Points ; i++){
			glVertex3d(pnt[i][0], pnt[i][1],-z0);
		}
	glEnd();

	//side of hand
	glMaterialfv(GL_FRONT, GL_AMBIENT, amb3);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, dif3);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe3);
	glMaterialf (GL_FRONT, GL_SHININESS, 10.);

	glBegin(GL_QUADS); 
		for (i = 0 ; i <= Hand_Points-2 ; i++){
			glVertex3d(pnt[i][0], pnt[i][1], z0);
			glVertex3d(pnt[i][0], pnt[i][1],-z0);
			glVertex3d(pnt[i+1][0], pnt[i+1][1],-z0);
			glVertex3d(pnt[i+1][0], pnt[i+1][1], z0);
		}
		glVertex3d(pnt[Hand_Points-1][0], pnt[Hand_Points-1][1], z0);
		glVertex3d(pnt[Hand_Points-1][0], pnt[Hand_Points-1][1],-z0);
		glVertex3d(pnt[0][0], pnt[0][1],-z0);
		glVertex3d(pnt[0][0], pnt[0][1], z0);
	glEnd();

	for (i = 0; i < 5; i++){
		finger[i]->draw();
	}
}
