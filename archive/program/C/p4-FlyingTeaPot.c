/* p4-FlyingTeaPot.c
 * Animate flying teapot.
 */

#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

double dist = -10.0;
double theta = 0.0;

void myKeyboard(unsigned char key, int x, int y)
{
	if (key == 27)
		exit(0);
}

void xyzAxes(double length)
{
	glBegin(GL_LINES);
	glColor3d(1.0, 1.0, 0.0); // yellow
	glVertex3d(0.0, 0.0, 0.0);
	glVertex3d(length, 0.0, 0.0); // x-axis
	glColor3d(1.0, 0.0, 0.0);	  // red
	glVertex3d(0.0, 0.0, 0.0);
	glVertex3d(0.0, length, 0.0); // y-axis
	glColor3d(0.0, 0.0, 1.0);	  // blue
	glVertex3d(0.0, 0.0, 0.0);
	glVertex3d(0.0, 0.0, length); // z-axis
	glEnd();
}

void myDisplay(void)
{
	int i = 0;

	glClear(GL_COLOR_BUFFER_BIT);

	glPushMatrix();
	/*		Move view point		*/
	gluLookAt(0.0, 1.0, dist, 0.0, 1.0, dist + 1.0, 0.0, 1.0, 0.0);
	xyzAxes(10.0);
	glPushMatrix();
	glTranslated(1.0, 2.0, 0.0);
	glRotated(theta, 1.0, 1.0, 0.0);
	glColor3d(1.0, 0.0, 0.0);
	glutWireTeapot(1.0);
	glPopMatrix();

	glColor3d(1.0, 1.0, 1.0); // draw floor
	glBegin(GL_LINES);
	for (i = -35; i < 36; i += 2)
	{
		glVertex3i(i, 0, -35);
		glVertex3i(i, 0, 35);
		glVertex3i(-50, 0, i);
		glVertex3i(50, 0, i);
	}
	glEnd();

	glPopMatrix();
	glutSwapBuffers();
}

void myIdle(void)
{
	dist += 0.03;
	if (dist >= -1.0)
		glutIdleFunc(NULL);
	theta = fmod(theta + 0.5, 360.0);
	glutPostRedisplay();
}

void myInit(char *progname)
{
	int width = 640, height = 480;

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(0, 0);
	glutCreateWindow(progname);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0, (double)width / (double)height, 0.1, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	myInit(argv[0]);
	glutKeyboardFunc(myKeyboard);
	glutIdleFunc(myIdle);
	glutDisplayFunc(myDisplay);
	glutMainLoop();
	return 0;
}
