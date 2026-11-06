// Q12 [Medium] — Front and back materials 
#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include <GL/freeglut.h>
using namespace std;

float rotationAngle = 0.0f;

void init()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

    GLfloat lightPosition[] = {0.0f, 3.0f, 5.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

    GLfloat lightDiffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);

    GLfloat frontColor[] = {1.0f, 0.0f, 0.0f, 1.0f};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, frontColor);

    GLfloat backColor[] = {0.0f, 0.0f, 1.0f, 1.0f};
    glMaterialfv(GL_BACK, GL_DIFFUSE, backColor);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(0.0f, 0.0f, 6.0f,
              0.0f, 0.0f, 0.0f,
              0.0f, 1.0f, 0.0f);

    glRotatef(rotationAngle, 0.0f, 1.0f, 0.0f);

    // draw a polygon with front and back faces
    glBegin(GL_POLYGON);

        glNormal3f(0.0f, 0.0f, 1.0f);

        glVertex3f(-2.0f, -1.5f, 0.0f);
        glVertex3f( 2.0f, -1.5f, 0.0f);
        glVertex3f( 1.5f,  1.5f, 0.0f);
        glVertex3f(-1.5f,  1.5f, 0.0f);

    glEnd();

    glutSwapBuffers();
}

void update(int value)
{
    rotationAngle += 1.0f;

    if (rotationAngle >= 360.0f)
        rotationAngle = 0.0f;

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

void reshape(int width, int height)
{
    if (height == 0)
        height = 1;

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45.0, (double)width / height, 1.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Q12 - Front and Back Materials");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(16, update, 0);

    glutMainLoop();

    return 0;
}