/*  p4-RotateTeaPotPolarView.c
 *  Rotating tea pot is observed in polar view.
 */
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

double	theta = 0.0;						// angular of tea pot

void myKeyboard( unsigned char key, int x, int y )
{
	if (key == 27) exit(0);
}

void polarView(double distance, double twist, double elevation, double azimuth)
{
	glTranslated(0.0, 0.0, -distance);
	glRotated(-twist, 0.0, 0.0, 1.0);
	glRotated(-elevation, 1.0, 0.0, 0.0);
	glRotated(-azimuth, 0.0, 1.0, 0.0);
}

void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glPushMatrix();
    	polarView(5.0, 0.0, 10.0, theta);
		glColor3d(1.0, 1.0, 1.0);
		glutWireTeapot(1.0);
	glPopMatrix();
	glutSwapBuffers(); 
}

void myIdle(void)
{
	theta = fmod(theta + 0.5, 360.0);
	glutPostRedisplay();
}

void myInit(char *progname)
{
	int width = 500, height = 500;

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize( width, height);
	glutInitWindowPosition(0, 0); 
	glutCreateWindow(progname);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0, (double)width / (double)height, 0.1, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv); 
	myInit(argv[0]);
	glutKeyboardFunc(myKeyboard);
    glutIdleFunc(myIdle);
    glutDisplayFunc(myDisplay);
	glutMainLoop(); 
	return 0;
}
