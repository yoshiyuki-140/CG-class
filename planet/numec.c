#include <stdlib.h>
#include <GL/glut.h>

static int year = 0, day = 0;
static int star1_year = 0, star2_year = 0, star3_year = 0, numec_year = 0;

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
    int evenness = 10;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3d(1.0, 1.0, 1.0);
    glPushMatrix();

    // 太陽 B
    glPushMatrix();
    glColor3d(1.0, 1.0, 0.0);
    glRotated((double)star1_year, 0.0, 1.0, 0.0);
    glTranslated(2.0, 0.0, 0.0);
    glutSolidSphere(0.4, 10 * evenness, 8 * evenness);

    // 太陽 C
    glPushMatrix();
    glColor3d(1.0, 0.5, 0.0);
    glRotated((double)star2_year, 0.0, 1.0, 0.0);
    glTranslated(0.5, 0.0, 0.0);
    glutSolidSphere(0.3, 10 * evenness, 8 * evenness);

    glPopMatrix();
    glPopMatrix();

    // 太陽A (中心の太陽)
    glColor3d(0.0, 1.0, 0.5);
    glutSolidSphere(1.0, 20 * evenness, 16 * evenness);

    // ナメック星
    glPushMatrix();
    glColor3d(0.0, 0.0, 1.0); // 惑星の色
    glRotated((double)numec_year, 0.0, 1.0, 0.0);
    glTranslated(4.0, 0.0, 0.0); // 外側の軌道に配置
    glutSolidSphere(0.3, 10 * evenness, 8 * evenness);
    glPopMatrix(); // 惑星のPopMatrix

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
    gluLookAt(0.0, 6.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
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
        numec_year = (numec_year + speed_of_year) % 360;
        glutPostRedisplay();
        break;
    case 'k':
        star1_year = (star1_year - speed_of_year) % 360;
        star2_year = (star2_year - 2 * speed_of_year) % 360;
        star3_year = (star3_year - 3 * speed_of_year) % 360;
        numec_year = (numec_year - speed_of_year) % 360;
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
