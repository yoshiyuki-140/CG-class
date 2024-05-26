#include <GL/glut.h>

void initLighting()
{
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat light_position[] = {1.0, 1.0, 1.0, 0.0};
    GLfloat diffuse_light[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat ambient_light[] = {0.2, 0.2, 0.2, 1.0};
    GLfloat specular_light[] = {1.0, 1.0, 1.0, 1.0};

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    // 恒星を描画
    glPushMatrix();
    glTranslatef(0.0, 0.0, 0.0);
    GLfloat emission[] = {1.0, 1.0, 0.0, 1.0}; // 黄色の発光
    glMaterialfv(GL_FRONT, GL_EMISSION, emission);
    glutSolidSphere(1.0, 20, 16);
    glPopMatrix();

    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Emissive Star Example");

    initLighting();
    glutDisplayFunc(display);
    glEnable(GL_DEPTH_TEST);

    glutMainLoop();
    return 0;
}
