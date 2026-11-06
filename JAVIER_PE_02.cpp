// Q02 [Easy] — Change ambient intensity
#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include <GL/freeglut.h>
using namespace std;

float ambientIntensity = 0.1f;

void setAmbientLight()
{
    GLfloat ambientLight[] = {
        ambientIntensity,
        ambientIntensity,
        ambientIntensity,
        1.0f
    };

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
}

void init()
{
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    GLfloat lightPosition[] = {2.0f, 3.0f, 3.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

    setAmbientLight();

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(4.0, 3.0, 5.0,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);

    setAmbientLight();

    glColor3f(1.0f, 0.7f, 1.0f);
    glutSolidCube(2.0);

    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        case '1':
            ambientIntensity = 0.1f;
            break;

        case '2':
            ambientIntensity = 0.4f;
            break;

        case '3':
            ambientIntensity = 0.8f;
            break;

        case 27:
            exit(0);
    }

    setAmbientLight();
    glutPostRedisplay();
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
    glutCreateWindow("Q02 - Change ambient intensity");

    init();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(reshape);

    glutMainLoop();

    return 0;
}