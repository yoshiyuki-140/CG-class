#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
#include <time.h>
#include "cboid.h"

using namespace std;

int		gMouseX, gMouseY;
int		gPitch = 30;
int		gYaw;
double	gTranslate = -3.5;

const int kNumBoids = 20;			// The number of fish
extern const double kRoomW = 6;		// width of 'the room'
extern const double kRoomH = 6;		// height of 'the room'
extern const double kRoomD = 6;		// depth of 'the room'

/* state variable for mouse dragging. (R and L button, respectively) */
enum _mousemode{
	eTranslate, eRotate,
}gMouseMode;

/* view point mode:
 * eFixed means fixed position, and eStalking means
 * that the observer (you) follow the #0 boid.
 * And, eNViewport is the number of this enumeration.
 */
enum _viewpoint{
	eFixed = 0, eStalking0, eNViewpoint
}gViewpoint;


CBoid **boid;

void myMouseFunc(int button, int state, int x, int y)
{
	if(button == GLUT_LEFT_BUTTON){		
		gMouseX = x-gYaw;
		gMouseY = y-gPitch;
		gMouseMode = eRotate;
	}
	if(button == GLUT_RIGHT_BUTTON){
		gMouseY = -y - (int)(gTranslate*40);
		gMouseMode = eTranslate;
	}
	if(button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN){
		gViewpoint = (_viewpoint)((gViewpoint + 1) % eNViewpoint);
	}
}

void myMotionFunc(int x, int y)
{
	if(gMouseMode == eRotate){
		gYaw = x - gMouseX;
		gPitch = y - gMouseY;
	}else if(gMouseMode == eTranslate){
		gTranslate = (-y - gMouseY)/40.0;
	}
}

void mySetLight(void)
{
	int	pos[]={0,1,-1,0};
	glLightiv(GL_LIGHT0, GL_POSITION, pos);
	glEnable(GL_LIGHT0);
}


void myDisplay(void)
{
	const float materialFloor[][4]  = {{0, 1, .8, 1},{0, .8, 1, 1},};

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);

	glPushMatrix();
	glTranslatef(0, 0, gTranslate);
	glRotatef(gPitch, 1, 0, 0);
	glRotatef(gYaw, 0, 1, 0);
	if(gViewpoint == eStalking0){     	// stalking mode
		glTranslatef(-boid[0]->getX(),	// translate the viewpoint to boid #0
					-boid[0]->getY(),
					-boid[0]->getZ()
					);
	}
//Question: Why the following "mySetLight()" is needed?
	mySetLight();

/* draw the floor */
	glNormal3f(0,0,1);
	for(int z = -(int)kRoomH * 10 / 2; z < (int)kRoomH * 10 / 2 - 1; z += 5){
	for(int x = -(int)kRoomW * 10 / 2; x < (int)kRoomW * 10 / 2 - 1; x += 5){
		glMaterialfv(GL_FRONT_AND_BACK,
					 GL_AMBIENT_AND_DIFFUSE,
					 materialFloor[(((z/5)&1) + ((x/5)&1))&1]
					);
		glBegin(GL_POLYGON);
		glVertex3f(x * .1,      - kRoomD / 2, z * .1);
		glVertex3f(x * .1 + .5, - kRoomD / 2, z * .1);
		glVertex3f(x * .1 + .5, - kRoomD / 2, z * .1 + .5);
		glVertex3f(x * .1,      - kRoomD / 2, z * .1 + .5);
		glEnd();
    }
  	}

/* draw boids */
	for(int i = 0; i < kNumBoids; i++){
		glPushMatrix();
		boid[i]->translate();
		boid[i]->rotate();
		boid[i]->draw();
		glPopMatrix();
	}
	glPopMatrix();
	glutSwapBuffers();
}

void myReshape(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0, (double)width / (double)height, 0.1, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void myKeyboard (unsigned char key, int x, int y)
{
	if (key == 27) exit (0);
}

void myTimer(int aArg)
{
	for(int i = 0; i < kNumBoids; i++){
		boid[i]->act(boid);
	}
	glutPostRedisplay();
	glutTimerFunc(33, myTimer, 0);
}

void myInit(char *progname)
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow(progname);
	glClearColor(.8, .8, .95, 1);
	glLoadIdentity();
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,1);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	myInit(argv[0]);
	mySetLight();
	glutKeyboardFunc(myKeyboard);
	glutMouseFunc(myMouseFunc);
	glutMotionFunc(myMotionFunc);
	glutTimerFunc(33, myTimer, 0);
	glutReshapeFunc(myReshape);
	glutDisplayFunc(myDisplay);

	srand48((int)time(NULL));
	boid = new CBoid* [kNumBoids + 1];
	boid[kNumBoids] = NULL;
	for(int i = 0; i < kNumBoids; i++){
		boid[i] = new CBoid();
		boid[i]->setPosition(drand48()*4-2, drand48()*4-2, drand48()*4-2);
		boid[i]->setVelocity(drand48()*2-1, drand48()*2-1, drand48()*2-1);
	}
	glutMainLoop();
	return 0;
}
