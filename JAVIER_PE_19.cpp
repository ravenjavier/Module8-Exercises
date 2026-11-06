// Q19 [Hard] — Two-material showroom
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

float rotationAngle = 0.0f;

void setupLighting()
{
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);

    GLfloat light0Position[] = {-3.0f, 4.0f, 4.0f, 1.0f};
    GLfloat light0Diffuse[] = {1.0f, 0.2f, 0.2f, 1.0f};
    GLfloat light0Specular[] = {1.0f, 0.8f, 0.8f, 1.0f};

    glLightfv(GL_LIGHT0, GL_POSITION, light0Position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0Diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light0Specular);

    GLfloat light1Position[] = {3.0f, 4.0f, 4.0f, 1.0f};
    GLfloat light1Diffuse[] = {0.2f, 0.2f, 1.0f, 1.0f};
    GLfloat light1Specular[] = {0.8f, 0.8f, 1.0f, 1.0f};

    glLightfv(GL_LIGHT1, GL_POSITION, light1Position);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1Diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light1Specular);

    GLfloat globalAmbient[] = {0.2f, 0.2f, 0.2f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbient);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
}

void setDullMaterial()
{
    GLfloat ambient[] = {0.5f, 0.1f, 0.1f, 1.0f};
    GLfloat diffuse[] = {0.8f, 0.2f, 0.2f, 1.0f};
    GLfloat specular[] = {0.15f, 0.15f, 0.15f, 1.0f};

    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT, GL_SHININESS, 8.0f);
}

void setShinyMaterial()
{
    GLfloat ambient[] = {0.1f, 0.1f, 0.5f, 1.0f};
    GLfloat diffuse[] = {0.2f, 0.3f, 0.8f, 1.0f};
    GLfloat specular[] = {1.0f, 1.0f, 1.0f, 1.0f};

    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT, GL_SHININESS, 100.0f);
}

void drawText(float x, float y, const char* text)
{
    glDisable(GL_LIGHTING);

    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(x, y);

    for (int i = 0; text[i] != '\0'; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    }

    glEnable(GL_LIGHTING);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(
        0.0, 2.0, 9.0,
        0.0, 0.0, 0.0,
        0.0, 1.0, 0.0
    );

    setupLighting();

    glRotatef(rotationAngle, 0.0f, 1.0f, 0.0f);

    glPushMatrix();
        glTranslatef(-2.0f, 0.0f, 0.0f);
        setDullMaterial();
        glutSolidSphere(1.2, 50, 50);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(2.0f, 0.0f, 0.0f);
        setShinyMaterial();
        glutSolidSphere(1.2, 50, 50);
    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
        glLoadIdentity();
        gluOrtho2D(-5.0, 5.0, -3.0, 3.0);

        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
            glLoadIdentity();

            drawText(-3.0f, -2.0f, "DULL MATERIAL");
            drawText(1.0f, -2.0f, "SHINY MATERIAL");

        glPopMatrix();

        glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);

    glutSwapBuffers();
}

void update(int value)
{
    rotationAngle += 1.0f;

    if (rotationAngle >= 360.0f)
    {
        rotationAngle = 0.0f;
    }

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

void reshape(int width, int height)
{
    if (height == 0)
    {
        height = 1;
    }

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45.0, (double)width / height, 1.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
}

void init()
{
    glClearColor(0.08f, 0.08f, 0.12f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1000, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Q19 - Two-Material Showroom");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(16, update, 0);

    glutMainLoop();

    return 0;
}