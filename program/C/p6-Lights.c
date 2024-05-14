/* p6-Lights.c
 * Demonstrates the useage of the lighting in OpenGL.
 * Two light sources illuminate the shpere.
 */

#include <stdlib.h>
#include <GL/glut.h>

void mySetLight()
{
	float light0_position[] = {  1.0,  1.0, 1.0, 1.0 };	// point light source
	float light1_position[] = { -1.0, -1.0, 1.0, 1.0 };	// point light source
	float light1_ambient[]  = { 0.0, 0.0, 0.5, 1.0 };
	float light1_diffuse[]  = { 0.0, 0.0, 1.0, 1.0 };
	float light1_specular[] = { 0.0, 0.0, 1.0, 1.0 };

/* Set up LIGHT0 which uses the default parameters except position */
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
/* Set up LIGHT1 */
	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
	glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);

	glEnable(GL_LIGHT0);		// enable the 0th light
	glEnable(GL_LIGHT1);		// enable the 1st light
}

void myInit(char *progname) 
{

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500); 
	glutInitWindowPosition(0, 0);
	glutCreateWindow(progname);

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);								// flat shading
}

void myDisplay(void)
{
	float mtrl_specular[]  = {1.0, 1.0, 1.0, 1.0};
	float mtrl_shininess[] = {50.0};					// range [0,128]

	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
/* Use z-buffer */
	glEnable(GL_DEPTH_TEST);
/* Enable the current lighting parameters to compute shading */
	glEnable(GL_LIGHTING);	
	
	glMaterialfv(GL_FRONT, GL_SPECULAR, mtrl_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mtrl_shininess);
	glutSolidSphere(1.0, 20, 16);						// sphere of radius one
	glFlush();
}

void myReshape (int width, int height)
{
	double	a = 1.5, z = 10.0;
	
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (width <= height)
		glOrtho (-a, a, -a*(double)height / (double)width,
				  a*(double)height/(double)width, -z, z);
	else
		glOrtho (-a*(double)width/(double)height,
			a*(double)width/(double)height, -a, a, -z, z);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void myKeyboard(unsigned char key, int x, int y)
{
   if ( key == 27 ) exit(0);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	myInit(argv[0]);
	mySetLight();
	glutKeyboardFunc(myKeyboard);
	glutReshapeFunc(myReshape);
	glutDisplayFunc(myDisplay);
	glutMainLoop();
	return 0;
}
