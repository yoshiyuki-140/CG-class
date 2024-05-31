/* p4-MovingPlanet.c
 * Animation for a solar system ( see p3-planet.c ) using by glutTimerFunc().
 */
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

int 	year = 0, day = 0;
int 	samplingTime = 50;

void myKeyboard(unsigned char key, int x, int y)
{
	if ( key == 27) exit (0);
}

void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3d(1.0, 1.0, 1.0);

	glPushMatrix();
		glutWireSphere(1.0, 20, 16);						// sun
		glRotated((double)year, 0.0, 1.0, 0.0);
		glTranslated(3.0, 0.0, 0.0);
		glRotated((double)day, 0.0, 1.0, 0.0);
		glutWireSphere(0.2, 10, 8);						// planet
	glPopMatrix();
	glutSwapBuffers();
}

void myInit(char *progname)
{
	int width = 500, height = 500;

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(0, 0);
	glutCreateWindow(progname);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0, (double)width / (double)height, 0.1, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 1.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void myTimer(int value)
{
	if (value==1)
	{
		glutTimerFunc(samplingTime,myTimer,1);
		year = (year+1) % 360;
		day  = (day+5) % 360;
		glutPostRedisplay();
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	myInit(argv[0]);
	glutKeyboardFunc(myKeyboard);
	glutTimerFunc(samplingTime, myTimer, 1);
	glutDisplayFunc(myDisplay); 
	glutMainLoop();
	return 0;
}
