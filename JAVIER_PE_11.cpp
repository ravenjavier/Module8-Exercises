// Q11 [Medium] — Spotlight cutoff
#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include <GL/freeglut.h>
using namespace std;

void setSpotlight(GLenum light, float x, float cutoff)
{
    GLfloat position[] = {x, 3.0f, 3.0f, 1.0f};
    glLightfv(light, GL_POSITION, position);

    GLfloat direction[] = {0.0f, -0.6f, -0.8f};
    glLightfv(light, GL_SPOT_DIRECTION, direction);

    glLightf(light, GL_SPOT_CUTOFF, cutoff);
    glLightf(light, GL_SPOT_EXPONENT, 0.0f);

    GLfloat diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glLightfv(light, GL_DIFFUSE, diffuse);
}

void init()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);

    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);

    setSpotlight(GL_LIGHT0, -3.0f, 15.0f);
    setSpotlight(GL_LIGHT1, 0.0f, 30.0f);
    setSpotlight(GL_LIGHT2, 3.0f, 60.0f);

    GLfloat diffuseColor[] = {0.3f, 0.7f, 1.0f, 1.0f};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseColor);

    GLfloat ambientColor[] = {0.05f, 0.05f, 0.05f, 1.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambientColor);

    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
}

void drawSphere(float x)
{
    glPushMatrix();
    glTranslatef(x, 0.0f, 0.0f);
    glutSolidSphere(0.8, 50, 50);
    glPopMatrix();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(0.0, 3.0, 11.0,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);

    // draw the three spheres
    drawSphere(-3.0f);
    drawSphere(0.0f);
    drawSphere(3.0f);

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
    glutInitWindowSize(900, 600);
    glutCreateWindow("Q11 - Spotlight Cutoff");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutMainLoop();

    return 0;
}