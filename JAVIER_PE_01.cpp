// Q01 [Easy] — Toggle lighting with the L key
#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include <cstdlib>
#include <GL/freeglut.h>
using namespace std;

bool lightingEnabled = true;

// initialize lighting
void init()
{
    glEnable(GL_DEPTH_TEST);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat lightPosition[] = {2.0f, 3.0f, 3.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

    GLfloat materialDiffuse[] = {0.2f, 0.7f, 1.0f, 1.0f};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
}

// draw a 3d object
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(
        4.0, 3.0, 5.0,
        0.0, 0.0, 0.0,
        0.0, 1.0, 0.0
    );

    glPushMatrix();
    glColor3f(0.2f, 0.7f, 1.0f);
    glutSolidCube(2.0);
    glPopMatrix();
    glutSwapBuffers();
}

// handle keyboard input
void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 'L':
        case 'l':
            lightingEnabled = !lightingEnabled;

            if (lightingEnabled)
            {
                glEnable(GL_LIGHTING);
                cout << "lighting: ON" << endl;
            }
            else
            {
                glDisable(GL_LIGHTING);
                cout << "lighting: OFF" << endl;
            }

            glutPostRedisplay();
            break;

        case 27:
            exit(0);
            break;
    }
}

// handle window resizing
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
    glutCreateWindow("Q01 - Toggle lighting with the L key");

    init();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(reshape);

    glutMainLoop();

    return 0;
}