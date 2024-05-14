/* code: p3-StackRotate.c 
 * The usage of glPushMatrix() and glPopMatrix(), and the synthetic trans-
 * formation of modeling are explained through drawing two cones.
 */
#include <stdlib.h>
#include <GL/glut.h>

void myKeyboard(unsigned char key, int x, int y)
{
	if(key == 27) exit(0);
}

void myDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT);
/* 1st cone */
	glColor3f(1.0, 0.0, 0.0);
	glPushMatrix();
		glRotatef(-90.0, 1.0, 0.0, 0.0);
		glTranslatef(1.0, 3.0, 0.0);
		glutWireCone(0.4, 1.0, 10, 10);
	glPopMatrix();
/* 2nd cone */
	glColor3f(0.0, 0.0, 1.0);
	glPushMatrix();
		glRotatef(90.0, 0.0, 1.0, 0.0);
		glTranslatef(3.0, 1.0, 0.0);
		glutWireCone(0.4, 1.0, 10, 10);
	glPopMatrix();

	glFlush();
}

void myInit(char *progname)
{
	int width = 500, height = 500;

	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(0, 0); 
	glutCreateWindow(progname);
	glClearColor(1.0, 1.0, 1.0, 0.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (float)width/(float)height, 0.1, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	myInit(argv[0]);
	glutDisplayFunc(myDisplay);
	glutKeyboardFunc(myKeyboard);
	glutMainLoop();
	return 0;
}
