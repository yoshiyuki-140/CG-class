/* p8-pendulemThree.cpp
 * Animation of three pendulum oscillation
 * The first is the same as p8-pendulum.cpp, the second and third are different
 * in the point of the initial angle and lenght, respectively.
 */
#include <iostream>
#include <math.h>
#include <GL/glut.h>
/* =========== Declaration and Data ========================================*/
void rungeKutta4th( void(*dfunc)(double *df, double *state, double t),
					int, double*, double, double );

const int		DIM = 2+1;
const double 	G 	= 9.80665;			// acceleration of gravity m/s/s
const double	DT	= 0.001;			// step size for Runge Kutta Method 
int				FrameCounter = 0;		// Frame counter to control frame
/*****************************************************************************
 *  Class CPendulum
 *****************************************************************************/
class CPendulum{						// Class of Pendulum 
	double	x, y, z;					// coordinates for endpoint of string
	double 	length;						// length of string
	double	theta;						// angle of pendulum
	double	velocity;					// velocity of pendulum
	double	size_w;						// width of weight
	double	size_h;						// height of weight
public:
	void	set(double x, double y, double z, double length,
				double theta, double velocity, double size_w, double size_h );
	void	draw();
	void	step();
	static void derivativeFunc(double *df, double *state, double t);
};
/*----------------------------------------------------------------------------
 * Set Initial values to pendulum state
 *----------------------------------------------------------------------------*/void CPendulum::set(double x0, double y0, double z0, double len,
					double the, double velo, double s_w, double s_h )
{
	x = x0;
	y = y0;
	z = z0;
	length   = len;
	theta    = (the/180.0)*M_PI;		// degree to radian
	velocity = velo;
	size_w   = s_w;
	size_h   = s_h;
}
/*----------------------------------------------------------------------------
 * Derivative functionn df(state, t)
 * state[0];theta, state[1];velocity, state[2];length(constant value)
 *----------------------------------------------------------------------------*/void CPendulum::derivativeFunc(double *df, double *state, double t)
{
	df[0] = state[1];
	df[1] = -(G/state[2])*sin(state[0]);
}
/*----------------------------------------------------------------------------
 * Solve the differential equation every one step
 *----------------------------------------------------------------------------*/void CPendulum::step()
{
	double st[DIM];						// state variables
	double t;							// time

	t = DT*(double)FrameCounter;
	st[0] = theta;
	st[1] = velocity;
	st[2] = length;
	rungeKutta4th(derivativeFunc, DIM, st, t, DT);
	theta = st[0];
	velocity = st[1];
}
/*----------------------------------------------------------------------------
 * Draw pendulum
 *----------------------------------------------------------------------------*/void CPendulum::draw()
{
	static float pndlmAmbient[]  = {0.1, 0.1, 0.1, 1.0};
	static float pndlmDiffuse[]  = {0.0, 8.0, 0.2, 1.0};
	static float pndlmSpecular[] = {0.0, 1.0, 1.0, 1.0};

	glMaterialfv(GL_FRONT, GL_AMBIENT, pndlmAmbient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, pndlmDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, pndlmSpecular);
	glMaterialf (GL_FRONT, GL_SHININESS, 128.0 );

	glPushMatrix();
		glDisable(GL_LIGHTING);			// disabling GL_LIGTING must be needed
		glColor3d(1.0,1.0,0.0);			// draw lines.
		glBegin(GL_LINES);				// draw line as string
			glVertex3d(x, y, z );
			glVertex3d(x + length*sin(theta), y - length*cos(theta), z);
		glEnd();
		glTranslated(x + length*sin(theta), y - length*cos(theta), z);
		glRotated(90.0, 1.0, 0.0, 0.0);	// rotate the cone around x-axis
		
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_LIGHTING);
			glutSolidCone(size_w, size_h, 20, 20);
		glDisable(GL_LIGHTING);
		glDisable(GL_DEPTH_TEST);
	glPopMatrix();
}
/*** End of class CPendulum **************************************************/

CPendulum pdlm, pdlm2, pdlm3;

void myDisplay(void)
{
	int i;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glTranslated(0.0, 0.5, -2.0);		// from viewpoint to object
	for (i=0; i<30; i++) {				// simulate 30 steps
		pdlm.step();
		pdlm2.step();
		pdlm3.step();
		FrameCounter++;
	}
	pdlm.draw();						// draw pendulum
	pdlm2.draw();
	pdlm3.draw();
	glPopMatrix();
	glutSwapBuffers();
}

void myReshape(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (double)width / (double)height, 0.1, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void myTimer(int value)					// time call back function
{
	if (value==1) {
		glutTimerFunc(30,myTimer,1);		// call back 30 fps
		glutPostRedisplay();
	}
}

void myKeyboard( unsigned char key, int x, int y )
{
	if ( key == 27 ) exit( 0 );
}

void myInit(char *progname)
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow(progname);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_NORMALIZE);
	glEnable(GL_AUTO_NORMAL);
}

void mySetLight()
{
	static float lightPos[] = {0.0, 1.0, 1.0, 0.0};
	
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glEnable(GL_LIGHT0);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	myInit(argv[0]);
	mySetLight();
    glutKeyboardFunc(myKeyboard);
	glutTimerFunc( 30,myTimer,1 );		// call back  30 fps
	glutReshapeFunc(myReshape);
	glutDisplayFunc(myDisplay);

	pdlm.set(0.0, 0.0, 0.0, 1.0, 60.0, 0.0, 0.1, 0.2);
	pdlm2.set(0.0, 0.0, -1.0, 1.0, 10.0, 0.0, 0.1, 0.2);
	pdlm3.set(0.0, 0.0, -2.0, 0.6, 60.0, 0.0, 0.1, 0.2);

	glutMainLoop();
	return 0;
}
