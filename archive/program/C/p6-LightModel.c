/* p6-LightModel.c
 * Demonstrate shading the outside and inside of the box.
 */

#include <stdlib.h>
#include <GL/glut.h>

int		gPitch = 30;
int		gYaw = 30;

void mySetLight()
{
	float light0_position[] = {  1.0,  1.0, 1.0, 1.0 };

/* LIGHT0 uses the default parameters except position */
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
	glEnable(GL_LIGHT0);
/* Shading the both sides of box */
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
}

void myInit(char *progname) 
{											//    GLUT_DEPTH be explained later
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(500, 500); 
	glutInitWindowPosition(0, 0);
	glutCreateWindow(progname);
	glClearColor(0.2, 0.0, 0.3, 1.0);		// dark blue
	glShadeModel(GL_FLAT);
}

void myDisplay(void)
{
	float ambient[]  = {0.7, 0.7, 0.7, 1.0};
	float diffuse[]  = {0.75, 0.75, 0.75, 1.0};
	float specular[] = {0.25, 0.25, 0.25, 1.0};
	float insideface[] = {1.0, 0.0, 0.0, 1.0};

	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // be explained later

	glEnable(GL_DEPTH_TEST);							 // ditto
	glEnable(GL_LIGHTING);
	
/* Set up the attribution for outside of box */
	glMaterialfv(GL_FRONT, GL_AMBIENT,  ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE,  diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT, GL_SHININESS, 50);
/* Set up the attribution for inside of box */
	glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, insideface);
	glMaterialf(GL_BACK,  GL_SHININESS, 60);

	glPushMatrix();
	glRotated((double)gPitch, 1, 0, 0);
	glRotated((double)gYaw,   0, 0, 1);

/* draw a box */
	glBegin(GL_QUADS);
/* back side (z<0) */
	glNormal3d(0, 0, -1);
	glVertex3d(-1, -1, -1);
	glVertex3d(-1,  1, -1);
	glVertex3d( 1,  1, -1);
	glVertex3d( 1, -1, -1);
/* right side (x>0) */
	glNormal3d(1,  0, 0);
	glVertex3d(1, -1, -1);
	glVertex3d(1,  1, -1);
	glVertex3d(1,  1,  1);
	glVertex3d(1, -1,  1);
/* left side (x<0) */
	glNormal3d(-1,  0, 0);
	glVertex3d(-1, -1, -1);
	glVertex3d(-1, -1,  1);
	glVertex3d(-1,  1,  1);
	glVertex3d(-1,  1, -1);
/* top side (y>0)*/
	glNormal3d(0, 1, 0);
	glVertex3d(-1, 1, -1);
	glVertex3d(-1, 1,  1);
	glVertex3d( 1, 1,  1);
	glVertex3d( 1, 1, -1);
/* bottom side (y<0) */
	glNormal3d(0, -1, 0);
	glVertex3d(-1, -1, -1);
	glVertex3d( 1, -1, -1);
	glVertex3d( 1, -1,  1);
	glVertex3d(-1, -1,  1);
	glEnd();

	glPopMatrix();
	glutSwapBuffers();

}

void myReshape (int width, int height)
{
	double	a = 3.0, z = 20.0;
	
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

void myTimer(int value)
{
	if (value == 1){
		glutTimerFunc(30, myTimer, 1);
		gYaw = (gYaw+1) % 360;
		gPitch = (gPitch+1) % 360;
		glutPostRedisplay();
	}
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
	glutTimerFunc(30, myTimer, 1);
	glutReshapeFunc(myReshape);
	glutDisplayFunc(myDisplay);
	glutMainLoop();
	return 0;
}
