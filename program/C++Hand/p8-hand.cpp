/* p8-hand.cpp
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include "mylib.h"
#include "CHand.h"
#include "CFinger.h"

unsigned char	mouseFlag = GL_FALSE;		// flag for moving or not
int				mouseXStart, mouseYStart;	// start position when drug begins
double			mouseXAngle = 0.0, mouseYAngle = 0.0;
int				frameCounter = 0;

CHand hand;

void moveFinger(int frameCounter)
{
	int		i, angle0, angle1, angle2;
	double	omg = 0.1, q, cq;
	static	double	the0 = 90/2, the1 = 110/2, the2 = 75/2;	// for four finger
	static	double	tthe0 = 90/2, tthe2 = 120/2;			// for thumb
	
	q = omg * (double)frameCounter;				// angle for finger joint
	cq = -cos(q);
/* rotate joints of the four finger */
	for (i = 1 ; i <= 4 ; i++){
		angle2 = (int)(the2*cq + the2);
		angle1 = (int)(the1*cq + the1);
		angle0 = (int)(the0*cq + the0);
		hand.finger[i]->rotateAngle(2, 2, angle2);
		hand.finger[i]->rotateAngle(2, 1, angle1);
		hand.finger[i]->rotateAngle(2, 0, angle0);
	}
/* rotate joints of thumb */
	angle2 = (int)((tthe2*cq + tthe2)*(cq+1)*(cq+1)/4);
	angle0 = (int)((tthe0*cq + tthe0)*(cq+1)*(cq+1)/4);
	hand.finger[0]->rotateAngle(2, 2, angle2);
	hand.finger[0]->rotateAngle(2, 0, angle0);
}	

void myDisplay(void)
{
	int	i;
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);

	glColor3d(1.0,1.0,1.0);

	glPushMatrix();
	glRotated(mouseXAngle, 1.0, 0.0, 0.0);
	glRotated(mouseYAngle, 0.0, 1.0, 0.0);
	moveFinger(frameCounter);
	hand.draw();
	glPopMatrix();

	glutSwapBuffers();
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
}

void myReshape(int width, int height)
{
	double	coef = 15, znear = -10, zfar = 10;;

	glViewport(0, 0, width, height); 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (width <= height)
		glOrtho(-coef, coef,-coef*(double)height/(double)width,
			coef*(double)height/(double)width, znear, zfar);
	else
		glOrtho(-coef*(double)width/(double)height,
			coef*(double)width/(double)height, -coef, coef, znear, zfar);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslated(0.0, -8.0, 0.0);
}

void myKeyboard (unsigned char key, int x, int y)
{
	if (key == 27) exit (0);
}

void mySetLight()
{
	float lightPos0[] = {0.0, 1.0, 0.0, 0.0};
    float ambient0[]  = {0.5, 0.5, 0.5, 1.0};
    float diffuse0[]  = {0.9, 0.9, 0.9, 1.0};
    float specular0[] = {0.4, 0.4, 0.4, 1.0};

	/* Set up Light0 */
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular0);

	glEnable(GL_LIGHT0);
}

void myTimer(int value)
{
	if (value == 1){
		glutTimerFunc(30, myTimer, 1);
		glutPostRedisplay();
		frameCounter++;
	}
}

void myMouseMotion(int x, int y)
{
	int	xdis, ydis;
	float	a = 0.5;
	
	if ( mouseFlag == GL_FALSE ) return;
	xdis = x - mouseXStart;
	ydis = y - mouseYStart;
/*
 * To match mouse's movement and its rotation axis
 */
	mouseXAngle += (double)ydis *a;
	mouseYAngle += (double)xdis *a;
	
	mouseXStart = x;
	mouseYStart = y;
}

void myMouseFunc(int button, int state, int x, int y)
{
	if ( button == GLUT_LEFT_BUTTON  && state == GLUT_DOWN ){
		mouseXStart = x;
		mouseYStart = y;
		mouseFlag = GL_TRUE;
	}
	else {
		mouseFlag = GL_FALSE;
	}
}

void myInit(char *progname) 
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow(progname);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_NORMALIZE);
	glEnable(GL_AUTO_NORMAL);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	myInit(argv[0]);
	mySetLight();
	glutKeyboardFunc(myKeyboard);
	glutMouseFunc(myMouseFunc);
	glutMotionFunc(myMouseMotion);
	glutTimerFunc(30, myTimer, 1);	
	glutReshapeFunc(myReshape);
	glutDisplayFunc(myDisplay); 
	glutMainLoop();
	return 0;
}
