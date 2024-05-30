// TEAPOT sample code
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

double theta = 0.0;

void myDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    glRotated(theta, 0.0, 1.0, 0.0);
    glColor3d(1.0, 1.0, 1.0);
    glutWireTeapot(1.0);
    glPopMatrix();

    glutSwapBuffers();
}

// アクションがない時に実行される関数。
void myIdle(void)
{
    theta = fmod(theta + 0.5, 360.0);
    glutPostRedisplay();
}

void myInit(char *progname)
{
    int width = 500, height = 500;

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(0, 0);
    glutCreateWindow(progname);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.0, (double)width / (double)height, 0.1, 20.0);
    glMatrixMode(GL_MODELVIEW);
}
