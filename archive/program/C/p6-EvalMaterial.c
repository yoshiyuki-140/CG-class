/* p6-EvalMaterial.c
 * When three parameters such as ambient, diffuse and specular are changed
 * respectively, the reflection of the gray shpere object is evaluated.
*/

#include <stdlib.h>
#include <GL/glut.h>

void myInit(char *progname) 
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500); 
	glutInitWindowPosition(0, 0);
	glutCreateWindow(progname);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
}

void mySetLight()
{
	float	light_position[] = {1.0, 1.0, 1.0, 0.0};
	float	light_ambient[] = {0.1, 0.1, 0.1, 1.0};
	
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glEnable(GL_LIGHT0);
}

void myDisplay()
{
	float	mtrl_shininess = 50.0;
	float	mtrl_v[4],mtrl_c[4]={ 0.5, 0.5, 0.5, 1.0 };
	int		i, j;
	float	x,y;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);						// use z-buffer
	glEnable(GL_LIGHTING);							// compute shading

	for ( i=1; i<=3; i++ ){
		y = 2.5 - (i-1)*2.5;
		for ( j=1; j<=5; j++ ){
			x = -5.0 + (j-1)*2.5;
			mtrl_v[0] = mtrl_v[1] = mtrl_v[2] = (j-1)*0.25;
			mtrl_v[3] = 1.0;
			switch (i){
				case 1:
					glMaterialfv(GL_FRONT, GL_AMBIENT, mtrl_v);
					glMaterialfv(GL_FRONT, GL_DIFFUSE, mtrl_c);
					glMaterialfv(GL_FRONT, GL_SPECULAR, mtrl_c);
					glMaterialf(GL_FRONT, GL_SHININESS, mtrl_shininess);
					break;
				case 2:
					glMaterialfv(GL_FRONT, GL_AMBIENT, mtrl_c);
					glMaterialfv(GL_FRONT, GL_DIFFUSE, mtrl_v);
					glMaterialfv(GL_FRONT, GL_SPECULAR, mtrl_c);
					glMaterialf(GL_FRONT, GL_SHININESS, mtrl_shininess);
					break;
				case 3:
					glMaterialfv(GL_FRONT, GL_AMBIENT, mtrl_c);
					glMaterialfv(GL_FRONT, GL_DIFFUSE, mtrl_c);
					glMaterialfv(GL_FRONT, GL_SPECULAR, mtrl_v);
					glMaterialf(GL_FRONT, GL_SHININESS, mtrl_shininess);
					break;
			}
			glPushMatrix();
			glTranslatef(x, y, 0.0);
			glutSolidSphere(1.0, 20, 16);	// the radius one of the sphere
			glPopMatrix();
		}
	}
	glFlush ();
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
}

void myReshape (int width, int height)
{
	double	ratio, a = 6.5;
	
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
