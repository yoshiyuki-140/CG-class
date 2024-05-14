/*  p6-LightPosition.c
 *  Examination of a light position.
 */
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

double	 theta = 0.0;						// angular of tea pot
float mtrl_diffuse[]   = {0.6, 0.6, 0.6, 0.0};
float mtrl_specular[]  = {1.0, 0.1, 0.3, 0.0};
float mtrl_shininess[] = {128.0};					// range [0,128]

float	light_pos[] = {5, 0, 0, 1};

void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);

	glPushMatrix();
//(3)	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
		glTranslated(0.0, 0.0, -3.0);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mtrl_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mtrl_specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, mtrl_shininess);
//(2)	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    	glRotated(theta, 0.0, 1.0, 0.0);
//(1)	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
		glutSolidTeapot(1.0);
	glPopMatrix();

	glutSwapBuffers(); 
}

void myIdle(void)
{
	theta = fmod(theta + 0.5, 360.0);
	glutPostRedisplay();
}

void myInit (char *progname)
{
    int width = 500, height = 500;

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize( width, height);
	glutInitWindowPosition(0, 0); 
	glutCreateWindow(progname);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0, (double)width/(double)height, 0.1, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void myKeyboard( unsigned char key, int x, int y )
{
    if ( key == 27 ) exit( 0 );
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv); 
	myInit(argv[0]);
	glEnable(GL_LIGHT0);
	glutKeyboardFunc(myKeyboard);
	glutIdleFunc(myIdle);
	glutDisplayFunc(myDisplay);
	glutMainLoop(); 
	return 0;
}
