/*  p2-2.c
 *  Examination of the relationship between the FRONT or BACK and the location
 *  of the vertex coordinates in an object.
 */
#include <stdlib.h>
#include <GL/glut.h>

void myKeyboard(unsigned char key, int x, int y)
{
	if (key == 27) exit(0);
}

void myDisplay()
{
	double	a=0.3, b=0.7;

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3d(1.0, 0.0, 0.0);			// red
	glBegin(GL_LINES);					// straight line
		glVertex2d( -0.9, 0.9 );
		glVertex2d(  0.9, 0.9 );
	glEnd();
	glPolygonMode(GL_FRONT, GL_FILL);	// fill color if front
	glPolygonMode(GL_BACK, GL_LINE);	// draw line  if back

	glBegin(GL_QUADS);					// counter-clockwise as front
		glVertex2d(a, -b); glVertex2d(b, -b);
		glVertex2d(b,  b); glVertex2d(a,  b);
	glEnd();

	glBegin(GL_QUADS);					// clockwise as back
		glVertex2d(-a,  b); glVertex2d(-a, -b);
		glVertex2d(-b, -b); glVertex2d(-b,  b);
	glEnd();

	glFlush();
}

void myInit(char *progname)
{
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(500, 400);
	glutInitWindowPosition(0, 0);
	glutCreateWindow(progname);
	glClearColor(1.0, 1.0, 0.0, 0.0);
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
