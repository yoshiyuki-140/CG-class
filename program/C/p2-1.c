/* p2-1.c
 * Draw a rectangular on 2D
 */
#include <stdlib.h>
#include <GL/glut.h>

void myKeyboard(unsigned char key, int x, int y)
{
	if (key == 27) exit(0);
}

void myDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT);		// clear color buffer and depth buffer
	glColor3d(1.0, 0.0, 0.0);			// red
	glBegin(GL_POLYGON);
		glVertex2d(-0.5, -0.5);
		glVertex2d( 0.5, -0.5);
		glVertex2d( 0.5,  0.5);
		glVertex2d(-0.5,  0.5);
	glEnd();
	glFlush();
}

void myInit(char *progname)
{
	glutInitDisplayMode(GLUT_RGBA);		// RGB and alpha mode
	glutInitWindowSize(500, 400);		// width and height
	glutInitWindowPosition(0, 0); 		// set origin of the window
	glutCreateWindow(progname);
	glClearColor(1.0, 1.0, 0.0, 0.0);	// yellow
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
