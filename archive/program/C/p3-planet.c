/* List: p3-planet.c
 * The planet turns around the sun. 
 * Examination of world-local coordinates, modeling transfomation and 
 * operation of matrix stack.
 */
#include <stdlib.h>
#include <GL/glut.h>

static int year = 0, day = 0;

void myInit(char *progname) 
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(500, 500); 
	glutInitWindowPosition(0, 0);
	glutCreateWindow(progname);
	glClearColor(0.0, 0.0, 0.0, 0.0);
}

void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3d(1.0, 1.0, 1.0);

	glPushMatrix();
		glutWireSphere(1.0, 20, 16);   /* sun */
		glRotated((double) year, 0.0, 1.0, 0.0);
		glTranslated(2.0, 0.0, 0.0);
		glRotated((double) day, 0.0, 1.0, 0.0);
		glutWireSphere(0.2, 10, 8);    /* planet */
	glPopMatrix();
	glutSwapBuffers();
}

void myReshape(int width, int height)
{
	glViewport(0, 0, width, height); 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (double)width/(double)height, 0.1, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void myKeyboard(unsigned char key, int x, int y)
{
   switch (key) {
      case 'd':
         day = (day + 10) % 360;
         glutPostRedisplay();
         break;
      case 'D':
         day = (day - 10) % 360;
         glutPostRedisplay();
         break;
      case 'y':
         year = (year + 5) % 360;
         glutPostRedisplay();
         break;
      case 'Y':
         year = (year - 5) % 360;
         glutPostRedisplay();
         break;
      case 27:
         exit(0);
         break;
      default:
         break;
   }
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	myInit(argv[0]);
	glutKeyboardFunc(myKeyboard);
	glutReshapeFunc(myReshape);
	glutDisplayFunc(myDisplay); 
	glutMainLoop();
	return 0;
}
