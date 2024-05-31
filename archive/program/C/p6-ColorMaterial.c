/* p6-ColorMaterial.c
 * Examines to draw various color to the box by giving the values of
 * RGBA with pop-up menu.
 */

#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <stdarg.h>

enum EMaterial {eAmbient = 0, eDiffuse, eSpecular};

char *const kMenuStr1[]={"Ambient", "Diffuse", "Specular",};
char *const kMenuStr2[]={"Red", "Green", "Blue", "Alpha",};

/* Attribution of outside of the box */
float gBox[][4] = {
  {.70, .70, .70, 1},  /* ambient  RGBA */
  {.75, .75, .75, 1},  /* diffuse  RGBA */
  {.25, .25, .25, 1},  /* specular RGBA */
};
/* Attribution of inside of the box */
const float kBoxInside[]  = {1, 0, 0, 1};
/* Window size */
int gWidth;
int gHeight;

/* The base positions of mouse be used when rotating the box with 
 * mouse dragging. These values are refreshed when clicking mouse 
 */
int gMouseX;
int gMouseY;

/* Angles for rotating the box */
int gYaw   =   0;
int gPitch = -60;

/* Function which can be used like printf() of C language.
 * The position of beginning write of the character is (x,y).
 */ 
void myPrintf(int x, int y, char *aFmt, ...){
	int  i;
	char buf[1024];
	va_list ap;					// defined in <stdarg.h>

	glPushMatrix();
	glLoadIdentity();
	va_start(ap, aFmt);			// defined in <stdarg.h>
	vsprintf(buf, aFmt, ap);	// ditto
	glRasterPos3d(0,0,-2);
	glBitmap(0, 0, 0, 0, (int)x, (int)y, NULL);  /* adjust position */
	for(i = 0; i < strlen(buf); i++){
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, buf[i]);
	}
	va_end(ap);
	glPopMatrix();
}

void myDisplay(){
	int i;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();

	glRotated(gPitch, 1, 0, 0);
	glRotated(  gYaw, 0, 0, 1);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
/* Set up the attribution for outside of box */
	glMaterialfv(GL_FRONT, GL_AMBIENT,  gBox[eAmbient]);
	glMaterialfv(GL_FRONT, GL_DIFFUSE,  gBox[eDiffuse]);
	glMaterialfv(GL_FRONT, GL_SPECULAR, gBox[eSpecular]);
	glMaterialf(GL_FRONT, GL_SHININESS, 120);
/* Set up the attribution for inside of box */
	glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, kBoxInside);
	glMaterialf(GL_BACK,  GL_SHININESS, 60);

/* draw a box */
	glBegin(GL_QUADS);
/* back side (z>0) */
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

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);		// be needed for drawing the characters below
	
	glColor3d(.1, .4, .1);
	for(i = 0; i < 3; i++){
		myPrintf(-gWidth/4, -gHeight/2+30-12*i,
				"%8s: %.2f, %.2f, %.2f, %.2f",
             	kMenuStr1[i],
             	gBox[i][0], gBox[i][1], gBox[i][2], gBox[i][3]
		);
	}
	glutSwapBuffers();
	glPopMatrix();
}

void myReshape(int width, int height)
{
	gWidth = width;
	gHeight = height;
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (double)width / (double)height, 0.1, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0, 0, -5.0);
}

void myMotionFunc(int x, int y)
{
	gYaw   = x - gMouseX;
	gPitch = y - gMouseY;
	glutPostRedisplay();
}

void myMouseFunc(int button, int state, int x, int y)
{
	if(button == GLUT_LEFT_BUTTON){
		gMouseX = x - gYaw;
		gMouseY = y - gPitch;
	}
}

void myKeyboard(unsigned char key, int x, int y)
{
	if ( key == 27 ) exit (0);
}

/* The lower three bytes of the argument is encoded such as 
 * [23..16]bit represents (ambient=0, diffuse=1, specular=2)
 * [15.. 8]bit represents value of RGBA
 * [ 7.. 0]bit represents intensity 0% to 100 % (100& is equal to 0xFF )
 */ 
void getValueFromMenu(int value)
{
	gBox[value >> 16][(value >> 8) & 0xff] = (double) (value & 0xff) / 0xff;
	glutPostRedisplay();
}

void mySetMenu()
{
	int i, j, k;
	int topmenu;
	int menu[3];                 /* ambient, diffuse, specular */
	int submenu[4];              /* r, g, b, a */
	char buf[128];

	for (i = 0; i < 3; i++){
		for (j = 0; j < 4; j++){
			submenu[j] = glutCreateMenu(getValueFromMenu);
			for (k = 0; k <= 100; k += 25){
				sprintf(buf, "%d%%", k);
				glutAddMenuEntry(buf, (i << 16) | (j << 8) | (k*255/100));
			}
		}
		menu[i] = glutCreateMenu(getValueFromMenu);
		for (j = 0; j < 4; j++){
			glutAddSubMenu(kMenuStr2[j], submenu[j]);
		}
	}
	topmenu = glutCreateMenu(getValueFromMenu);
	for (i = 0; i < 3; i++){
		glutAddSubMenu(kMenuStr1[i], menu[i]);
	}
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void mySetLight()
{
	float pos[] = { 2,  0,  1, 1};
	float amb[] = {.2, .2, .2, 1};
	float dif[] = {.7, .7, .7, 1};
	float spe[] = { 1,  1,  1, 1};

	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, dif);
	glLightfv(GL_LIGHT0, GL_SPECULAR, spe);

	glEnable(GL_LIGHT0);
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 1);
}

void myInit(char *progname)
{
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow(progname);
	glClearColor(0.8, 0.8, 0.95, 1.0);
	glShadeModel(GL_SMOOTH);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	myInit(argv[0]);
	mySetLight();
	mySetMenu();
    glutKeyboardFunc(myKeyboard);
	glutMouseFunc(myMouseFunc);
	glutMotionFunc(myMotionFunc);
	glutReshapeFunc(myReshape);
	glutDisplayFunc(myDisplay);
	glutMainLoop();
	return 0;
}
