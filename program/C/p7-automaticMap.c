/* p7-automaticMap.c
 * Demonstrates the usage of automatic mapping by using two objects.
 */
#include <stdio.h>
#include <GL/glut.h>

#define imageWidth		64
#define imageHeight		64

unsigned char texImage[imageHeight][imageWidth][4];

void makeTexImage(void)
{
	int i, j, c;

	for (i = 0; i < imageHeight; i++) {
		for (j = 0; j < imageWidth; j++) {
			c = ((((i&0x8)==0)^((j&0x8)==0)))*255;
			texImage[i][j][0] = (unsigned char)c;
			texImage[i][j][1] = (unsigned char)0;
			texImage[i][j][2] = (unsigned char)~c;
			texImage[i][j][3] = (unsigned char)255;
		}
	}
}

void setupTextures(void)
{
	makeTexImage();

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,imageWidth ,imageHeight,0,
								GL_RGBA, GL_UNSIGNED_BYTE, texImage);
/* automatic mapping */
	glTexGenf(GL_S,GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR);
	glTexGenf(GL_T,GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
}

void myInit(char *progname)
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow(progname);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHT0);
}

void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);

	glPushMatrix();
	glTranslated(-1.0, 0.0, 0.0);
	glutSolidSphere(0.8, 20, 20);
	glTranslated(2.0, 0.0, 0.0);
	glRotated(30.0, 0.0, 1.0, 0.0);
	glRotated(30.0, 1.0, 0.0, 0.0);
	glutSolidCube(1.0);
	glPopMatrix();
	glFlush();
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_TEXTURE_2D);

}

void myReshape(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (double)width / (double)height, 0.1, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslated(0.0, 0.0, -3.6);
}

void myKeyboard(unsigned char key, int x, int y)
{
	if (key == 27) exit (0);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	myInit(argv[0]);
	setupTextures();
	glutKeyboardFunc(myKeyboard);
	glutReshapeFunc (myReshape);
	glutDisplayFunc(myDisplay);
	glutMainLoop();
	return 0;
}
