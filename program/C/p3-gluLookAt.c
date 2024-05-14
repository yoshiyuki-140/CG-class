/* p3-gluLookAt.c 
 * Examination of gluLookAt command
 */

#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

void myKeyboard(unsigned char key, int x, int y)
{
	if(key == 27) exit(0);
}

void xyzAxes(double length)
{
	glBegin( GL_LINES );
		glColor3d(1.0, 0.0, 0.0);	// x-axis, red
		glVertex3d(0.0, 0.0, 0.0); glVertex3d(length, 0.0, 0.0);
		glColor3d(0.0, 1.0, 0.0);	// y-axis, green
		glVertex3d(0.0, 0.0, 0.0); glVertex3d(0.0, length, 0.0);
		glColor3d(0.0, 0.0, 1.0);	// z-axis, blue
		glVertex3d(0.0, 0.0, 0.0); glVertex3d(0.0, 0.0, length);
	glEnd();

}

void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	xyzAxes(1.0);
/* 1st cone */
	glColor3d(1.0, 0.0, 0.0);
	glPushMatrix();
		glTranslated(1.0, 0.0, -3.0);
		glRotated(-90.0, 1.0, 0.0, 0.0);
		glutWireCone(0.4, 1.0, 10, 10 );
	glPopMatrix();
/* 2nd cone */
	glColor3d(0.0, 0.0, 1.0);
	glPushMatrix();
		glTranslated(0.0, 1.0, -3.0);
		glRotated(90.0, 0.0, 1.0, 0.0);
		glutWireCone(0.4, 1.0, 10, 10);
	glPopMatrix();

	glFlush();
}

void myInit(char *progname)
{
	int width = 500, height = 500;
	int i;
	double d[3], u[3], norm;
	double pe[3] = {1.0, 1.0, 3.0}, pc[3] = {0.0, 0.0, 0.0};


	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(0, 0); 
	glutCreateWindow(progname);
	glClearColor(1.0, 1.0, 1.0, 0.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (double)width/(double)height, 0.1, 20.0);
	glMatrixMode(GL_MODELVIEW);

	for ( i = 0; i < 3; i++ ) d[i] = pc[i] - pe[i];
	u[0] = d[0]*d[1];
	u[1] = d[1]*d[2];
	u[2] = -(d[0]*d[0] + d[1]*d[1]);
	norm = u[0]*u[0] + u[1]*u[1] + u[2]*u[2];
	norm = sqrt(norm);
	u[0] /= norm; u[1] /= norm ; u[2] /= norm;
	gluLookAt(pe[0], pe[1], pe[2], pc[0], pc[1], pc[2], u[0], u[1], u[2]);
//	gluLookAt(pe[0], pe[1], pe[2], pc[0], pc[1], pc[2], 0.0, 1.0, 0.0);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	myInit(argv[0]);
	glutKeyboardFunc(myKeyboard);
	glutDisplayFunc(myDisplay);
	glutMainLoop();
	return 0;
}
