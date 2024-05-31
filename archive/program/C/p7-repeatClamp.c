/* p7-repeatClamp.c
 * This program examines the repeat and clamp function in texture mapping
 * using a checkerboard image onto two rectangles.
 */
#include <stdio.h>
#include <GL/glut.h>

/*	Create checkerboard texture	*/
#define	imageWidth  64
#define	imageHeight 64

unsigned char texImage[imageHeight][imageWidth][4];

void makeTexImage()
{
	int i, j, c;
    
	for (i = 0; i < imageHeight; i++) {
      	for (j = 0; j < imageWidth; j++) {
         	c = ((((i&0x10)==0)^((j&0x10))==0))*255;
         	texImage[i][j][0] = (unsigned char) c;			// red
         	texImage[i][j][1] = (unsigned char) 0;			// green
         	texImage[i][j][2] = (unsigned char) ~c;			// blue
         	texImage[i][j][3] = (unsigned char) 255;		// alpha
		}
	}
}

void setUpTexure(void)
{
	makeTexImage();
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 
					0, GL_RGBA, GL_UNSIGNED_BYTE, texImage);
}

void myInit(char *progname)
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow(progname);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
}

void myDisplay(void)
{
	double	tc = 2.0;
	double	p0[]={-2.0, -1.0, 0.0}, p1[]={0.0, -1.0, 0.0},
			p2[]={0.0, 1.0, 0.0},   p3[]={-2.0, 1.0, 0.0};
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);

	glBegin(GL_QUADS);
	glTexCoord2d(0.0, 0.0); glVertex3dv(p0);
	glTexCoord2d(tc , 0.0); glVertex3dv(p1);
	glTexCoord2d(tc , tc ); glVertex3dv(p2);
	glTexCoord2d(0.0, tc ); glVertex3dv(p3);

	glTexCoord2d(0.0, 0.0); glVertex3d(1.0, -1.0, 0.0);
	glTexCoord2d(1.0, 0.0); glVertex3d(2.41421, -1.0, -1.41421);
	glTexCoord2d(1.0, 1.0); glVertex3d(2.41421, 1.0, -1.41421);
	glTexCoord2d(0.0, 1.0); glVertex3d(1.0, 1.0, 0.0);
	glEnd();

	glFlush();
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
	if (key == 27 ) exit (0);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	myInit(argv[0]);
	setUpTexure();
	glutKeyboardFunc(myKeyboard);
	glutReshapeFunc(myReshape);
	glutDisplayFunc(myDisplay);
	glutMainLoop();
	return 0; 
}
