/* p5-menu.c
 * Pop-up menu and bitmap character are examined.
 */
#include <stdlib.h>
#include <GL/glut.h>

double	sizeOfTeapot = 1.0;

void myKeyboard( unsigned char key, int x, int y )
{
	if ( key == 27 ) exit( 0 );
}

void myInit(char *progname)
{	
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow(progname);
	glClearColor(0.0, 0.0, 0.0, 1.0);
}

void myReshape(int width, int height)
{
	double	ratio, a = 5.0;
	
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if ( width <= height ){
		ratio = (double)height / (double)width;
		glOrtho( -a, a, -a*ratio, a*ratio, -10.0, 10.0);
	}
	else {
		ratio = (double)width / (double)height;
		glOrtho( -a*ratio, a*ratio, -a, a, -10.0, 10.0);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void getValueFromMenu(int value)
{
	switch(value){
		case 1:
			sizeOfTeapot = 0.5;
			break;
		case 2:
			sizeOfTeapot = 1.0;
			break;
		case 3:
			sizeOfTeapot = 2.0;
			break;
		default:
			break;
	}
}

void mySetMenu()
{
	glutCreateMenu(getValueFromMenu);
	glutAddMenuEntry("x 0.5", 1);
	glutAddMenuEntry("x 1.0", 2);
	glutAddMenuEntry("x 2.0", 3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void myDisplay()
{
	char text[20]="Size is";
	char *p;
	
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	glTranslated(0.0, 0.0, -3.0);
	glColor3d(1.0, 0.0, 0.0);
	glutWireTeapot(sizeOfTeapot);
	
	glRasterPos3d(-1.0,-3.0,0.0);
	sprintf((char *)(text + 7),"%4.1f",sizeOfTeapot);
	for (p=text; *p; p++){
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *p);
	}	
	glPopMatrix();
	glutSwapBuffers();
}

void myIdle(void)
{
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	myInit(argv[0]);
	mySetMenu();
    glutKeyboardFunc(myKeyboard);
	glutIdleFunc(myIdle);
	glutReshapeFunc(myReshape);
	glutDisplayFunc(myDisplay);
	glutMainLoop();
	return 0;
}
