/* p8-finger.cpp
 * move a finger
 */
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include "mylib.h"
#include "CFinger.h"

CFinger finger;

void myDisplay(void)
{
	double	len[3], rad[3], ang[3];

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);

	glColor3f(1.0,1.0,1.0);

	glPushMatrix();
	glRotated(-45.0, 0.0, 1.0, 0.0);
	finger.draw();
	glPopMatrix();
	glutSwapBuffers();
}

void myReshape (int width, int height)
{
	const float	coef = 10;

	glViewport(0, 0, width, height); 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (width <= height)
		glOrtho(-coef, coef,-coef*(double)height/(double)width,
			coef*(double)height/(double)width, -100.0, 100.0);
	else
		glOrtho(-coef*(double)width/(double)height,
			coef*(double)width/(double)height, -coef, coef, -100.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslated(0.0, -2.0, 0.0);
}

void myKeyboard (unsigned char key, int x, int y)
{
	switch (key) {
		case 'r':
			finger.rotateAngle(1, 2, +5);
			break;
		case 'R':
			finger.rotateAngle(1, 2, -5);
			break;
		case 'f':
			finger.rotateAngle(1, 1, +5);
			break;
		case 'F':
			finger.rotateAngle(1, 1, -5);
			break;
		case 'v':
			finger.rotateAngle(1, 0, +5);
			break;
		case 'V':
			finger.rotateAngle(1, 0, -5);
			break;
		case 27:
			exit(0);
			break;
		default:
			break;
	}
	glutPostRedisplay();
}

void mySetLight()
{
	float lightPos0[] = {0.0, 0.0, 1.0, 0.0};
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

void mySetFinger()
{
	double	len[]={5, 3, 2}, rad[]={1, 0.9, 0.9};
	int		ang[]={0, 0, 0};
	finger.set(0.0, 0.0, 0.0, 0, len, rad, ang);
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
	mySetFinger();
	glutKeyboardFunc(myKeyboard);
	glutReshapeFunc(myReshape);
	glutDisplayFunc(myDisplay); 
	glutMainLoop();
	return 0;
}
