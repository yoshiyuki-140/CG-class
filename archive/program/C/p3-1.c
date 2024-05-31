/* p3-1.c
 * Examination of view volume.
 */
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

void myKeyboard(unsigned char key, int x, int y)
{
	if ( key == 27 ) exit(0) ;
}

void myInit(char *progname)
{
	int		width = 500, height = 500;

	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(0, 0);
	glutCreateWindow(progname);
	glClearColor(1.0, 1.0, 1.0, 0.0);

	glMatrixMode(GL_PROJECTION);			// be explained later
	glLoadIdentity();						// ditto
	gluPerspective(60.0, (double)width / (double)height, 0.1, 20 );
}

void myDisplay()
{
	double	o = 0.0, a = 0.25, z1 = 0;

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3d(1.0, 0.0, 0.0);
	glBegin(GL_QUADS);						// draw a rectangular on xy-plane
		glVertex3d(o, o, z1); glVertex3d(a, o, z1);
		glVertex3d(a, a, z1); glVertex3d(o, a, z1);
	glEnd();
	glFlush();
}

int main( int argc, char** argv )
{
	glutInit(&argc, argv);
	myInit(argv[0]);
	glutKeyboardFunc(myKeyboard);
	glutDisplayFunc(myDisplay);
	glutMainLoop();
	return 0;
}
