// Q06 [Easy] — Directional versus point light
#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include <GL/freeglut.h>
using namespace std; 

void setLight(float w)
{
    GLfloat lightPosition[] = {2.0f, 3.0f, 3.0f, w};
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
}

void init()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat lightDiffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);

    GLfloat lightSpecular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);

    GLfloat diffuseColor[] = {0.2f, 0.6f, 1.0f, 1.0f};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseColor);

    GLfloat specularColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glMaterialfv(GL_FRONT, GL_SPECULAR, specularColor);

    glMaterialf(GL_FRONT, GL_SHININESS, 40.0f);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(0.0, 2.0, 9.0,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);

    // left sphere - directional light (w = 0)
    glPushMatrix();
    glTranslatef(-2.0f, 0.0f, 0.0f);

    setLight(0.0f);
    glutSolidSphere(1.2, 50, 50);

    glPopMatrix();

    // right sphere - point light (w = 1)
    glPushMatrix();
    glTranslatef(2.0f, 0.0f, 0.0f);

    setLight(1.0f);
    glutSolidSphere(1.2, 50, 50);

    glPopMatrix();

    glutSwapBuffers();
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
    glutCreateWindow("Q06 - Directional versus point light");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutMainLoop();

    return 0;
}