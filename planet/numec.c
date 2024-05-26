#include <stdlib.h>
#include <GL/glut.h>

static int year = 0, day = 0;
static int star1_year = 0, star2_year = 0, star3_year = 0;

void myInit(char *progname)
{
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(700, 700);
    glutInitWindowPosition(0, 0);
    glutCreateWindow(progname);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    GLfloat light_position[] = {0.0, 0.0, 1.0, 1.0};
    GLfloat white_light[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat ambient_light[] = {0.2, 0.2, 0.2, 1.0};
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glEnable(GL_LIGHT0);
    glClearColor(0.0, 0.0, 0.0, 0.0);
}

void myDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3d(1.0, 1.0, 1.0);
    glPushMatrix();

    // 恒星A (中心の黄色い星)
    glPushMatrix();
    glColor3d(1.0, 1.0, 0.0);
    glRotated((double)star1_year, 0.0, 1.0, 0.0);
    glTranslated(2.0, 0.0, 0.0);
    glutSolidSphere(0.1, 10, 8);

    // 恒星B (恒星Aの周りのオレンジの星)
    glPushMatrix();
    glColor3d(1.0, 0.5, 0.0);
    glRotated((double)star2_year, 0.0, 1.0, 0.0);
    glTranslated(0.5, 0.0, 0.0);
    glutSolidSphere(0.07, 10, 8);

    // 恒星C (恒星Bの周りの赤い星)
    glColor3d(1.0, 0.0, 0.0);
    glRotated((double)star3_year, 0.0, 1.0, 0.0);
    glTranslated(0.3, 0.0, 0.0);
    glutSolidSphere(0.05, 10, 8);

    glPopMatrix(); // 恒星CのPopMatrix
    glPopMatrix(); // 恒星BのPopMatrix
    glPopMatrix(); // 恒星AのPopMatrix

    // ナメック星 (緑色の惑星)
    glColor3d(0.0, 1.0, 0.5);
    glutSolidSphere(0.2, 20, 16);

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
    gluLookAt(0.0, 3.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void myKeyboard(unsigned char key, int x, int y)
{
    int speed_of_year = 1;
    switch (key)
    {
    case 'j':
        star1_year = (star1_year + speed_of_year) % 360;
        star2_year = (star2_year + 2 * speed_of_year) % 360;
        star3_year = (star3_year + 3 * speed_of_year) % 360;
        glutPostRedisplay();
        break;
    case 'k':
        star1_year = (star1_year - speed_of_year) % 360;
        star2_year = (star2_year - 2 * speed_of_year) % 360;
        star3_year = (star3_year - 3 * speed_of_year) % 360;
        glutPostRedisplay();
        break;
    case 27: // ESC key
        exit(0);
        break;
    default:
        break;
    }
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    myInit(argv[0]);
    glutKeyboardFunc(myKeyboard);
    glutReshapeFunc(myReshape);
    glutDisplayFunc(myDisplay);
    glutMainLoop();
    return 0;
}