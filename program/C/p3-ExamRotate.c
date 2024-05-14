/* p3-ExamRotate.c
 * Examination of the rotation and translation command
 */
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

void myKeyboard(unsigned char key, int x, int y)
{
	if(key == 27) exit(0);
}

void myInit(char *progname)
{
	int width = 500, height = 500, i;

	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(0, 0);
	glutCreateWindow(progname);
	glClearColor(1.0, 1.0, 1.0, 0.0);

	glMatrixMode(GL_PROJECTION);			// be explained later
	glLoadIdentity();						// ditto
	gluPerspective(60.0, (double)width / (double)height, 0.1, 20);
}

void myDisplay(void)
{
	double	z1 = -3.0;

	glClear(GL_COLOR_BUFFER_BIT);	
	glColor3d(1.0, 0.0, 0.0);
	glTranslated(0.0, 0.0, z1);
	glRotated(-90.0, 1.0, 0.0, 0.0);
	glutWireCone(0.5, 1.5, 10.0, 10.0);
	glFlush();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	myInit(argv[0]);
	glutKeyboardFunc(myKeyboard);
	glutDisplayFunc(myDisplay);
	glutMainLoop();
	return( 0 );
}
