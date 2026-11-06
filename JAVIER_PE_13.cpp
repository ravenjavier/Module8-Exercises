// Q13 [Medium] — Checkerboard quad
#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include <GL/freeglut.h>
using namespace std;

const int CHECKER_SIZE = 64;
GLubyte checkerboard[CHECKER_SIZE][CHECKER_SIZE][3];
GLuint textureID;

// generate a black-and-white rgb checkerboard
void generateCheckerboard()
{
    for (int y = 0; y < CHECKER_SIZE; y++)
    {
        for (int x = 0; x < CHECKER_SIZE; x++)
        {
            int checker = ((x / 8) + (y / 8)) % 2;

            if (checker == 0)
            {
                checkerboard[y][x][0] = 255;
                checkerboard[y][x][1] = 255;
                checkerboard[y][x][2] = 255;
            }
            else
            {
                checkerboard[y][x][0] = 0;
                checkerboard[y][x][1] = 0;
                checkerboard[y][x][2] = 0;
            }
        }
    }
}

void createTexture()
{
    generateCheckerboard();

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGB,
        CHECKER_SIZE,
        CHECKER_SIZE,
        0,
        GL_RGB,
        GL_UNSIGNED_BYTE,
        checkerboard
    );
}

// draw the textured quad
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glColor3f(1.0f, 1.0f, 1.0f);

    glBegin(GL_QUADS);

        glTexCoord2f(0.0f, 0.0f);
        glVertex2f(-0.8f, -0.8f);

        glTexCoord2f(1.0f, 0.0f);
        glVertex2f(0.8f, -0.8f);

        glTexCoord2f(1.0f, 1.0f);
        glVertex2f(0.8f, 0.8f);

        glTexCoord2f(0.0f, 1.0f);
        glVertex2f(-0.8f, 0.8f);

    glEnd();

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
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Q13 - Checkerboard Quad");

    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

    createTexture();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    glutMainLoop();

    return 0;
}