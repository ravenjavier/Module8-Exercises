// Q08 [Medium] — Move a light with arrow keys
#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include <GL/freeglut.h>
using namespace std;

// light position
float lightX = 2.0f;
float lightY = 3.0f;
float lightZ = 3.0f;

void updateLight()
{
    GLfloat lightPosition[] = {
        lightX,
        lightY,
        lightZ,
        1.0f
    };

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

    glMaterialf(GL_FRONT, GL_SHININESS, 50.0f);

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

    updateLight();

    // draw the sphere
    glutSolidSphere(1.5, 50, 50);

    glutSwapBuffers();
}

void specialKeys(int key, int x, int y)
{
    const float step = 0.5f;

    switch (key)
    {
        case GLUT_KEY_LEFT:
            lightX -= step;
            break;

        case GLUT_KEY_RIGHT:
            lightX += step;
            break;

        case GLUT_KEY_UP:
            lightY += step;
            break;

        case GLUT_KEY_DOWN:
            lightY -= step;
            break;
    }

    updateLight();

    cout << "Light position: X = " << lightX << ", Y = " << lightY << endl;

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
    glutCreateWindow("Q08 - Move a Light with Arrow Keys");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(specialKeys);

    glutMainLoop();

    return 0;
}