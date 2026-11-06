// Q14 [Medium] — Texture repeat versus clamp
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

#ifndef GL_CLAMP_TO_EDGE
#define GL_CLAMP_TO_EDGE 0x812F
#endif

GLuint textureID;

// generate a checkerboard texture
void generateTexture()
{
    const int SIZE = 64;
    GLubyte image[SIZE][SIZE][3];

    for (int y = 0; y < SIZE; y++)
    {
        for (int x = 0; x < SIZE; x++)
        {
            int checker = ((x / 8) + (y / 8)) % 2;

            if (checker == 0)
            {
                image[y][x][0] = 255;
                image[y][x][1] = 255;
                image[y][x][2] = 255;
            }
            else
            {
                image[y][x][0] = 0;
                image[y][x][1] = 0;
                image[y][x][2] = 0;
            }
        }
    }

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGB,
        SIZE,
        SIZE,
        0,
        GL_RGB,
        GL_UNSIGNED_BYTE,
        image
    );
}

void drawQuad(float left, float right)
{
    glBegin(GL_QUADS);

        glTexCoord2f(0.0f, 0.0f);
        glVertex2f(left, -0.6f);

        glTexCoord2f(3.0f, 0.0f);
        glVertex2f(right, -0.6f);

        glTexCoord2f(3.0f, 3.0f);
        glVertex2f(right, 0.6f);

        glTexCoord2f(0.0f, 3.0f);
        glVertex2f(left, 0.6f);

    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glColor3f(1.0f, 1.0f, 1.0f);

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    drawQuad(-0.9f, -0.05f);

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    drawQuad(0.05f, 0.9f);

    glDisable(GL_TEXTURE_2D);

    glutSwapBuffers();
}

void reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)
{
    if (key == 27)
    {
        glDeleteTextures(1, &textureID);
        exit(0);
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 500);
    glutInitWindowPosition(100, 100);

    glutCreateWindow("Q14 - Texture Repeat versus Clamp");

    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

    generateTexture();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    glutMainLoop();

    return 0;
}
