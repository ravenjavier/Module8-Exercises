// Q18 [Hard] — Texture filtering comparison
#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include <GL/freeglut.h>
using namespace std;

const int TEX_SIZE = 8;

GLuint textureNearest;
GLuint textureLinear;

unsigned char textureData[TEX_SIZE][TEX_SIZE][3];

void createTextureData()
{
    for (int y = 0; y < TEX_SIZE; y++)
    {
        for (int x = 0; x < TEX_SIZE; x++)
        {
            if ((x + y) % 2 == 0)
            {
                textureData[y][x][0] = 255;
                textureData[y][x][1] = 255;
                textureData[y][x][2] = 255;
            }
            else
            {
                textureData[y][x][0] = 30;
                textureData[y][x][1] = 100;
                textureData[y][x][2] = 220;
            }
        }
    }
}

void createTextures()
{
    createTextureData();

    glGenTextures(1, &textureNearest);
    glBindTexture(GL_TEXTURE_2D, textureNearest);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGB,
        TEX_SIZE,
        TEX_SIZE,
        0,
        GL_RGB,
        GL_UNSIGNED_BYTE,
        textureData
    );

    glGenTextures(1, &textureLinear);
    glBindTexture(GL_TEXTURE_2D, textureLinear);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGB,
        TEX_SIZE,
        TEX_SIZE,
        0,
        GL_RGB,
        GL_UNSIGNED_BYTE,
        textureData
    );

    glBindTexture(GL_TEXTURE_2D, 0);
}

void drawQuad(float x1, float x2, GLuint texture)
{
    glBindTexture(GL_TEXTURE_2D, texture);

    glBegin(GL_QUADS);

        glTexCoord2f(0.0f, 0.0f);
        glVertex2f(x1, -2.0f);

        glTexCoord2f(1.0f, 0.0f);
        glVertex2f(x2, -2.0f);

        glTexCoord2f(1.0f, 1.0f);
        glVertex2f(x2, 2.0f);

        glTexCoord2f(0.0f, 1.0f);
        glVertex2f(x1, 2.0f);

    glEnd();
}

void drawText(float x, float y, const char* text)
{
    glRasterPos2f(x, y);

    for (int i = 0; text[i] != '\0'; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glEnable(GL_TEXTURE_2D);

    drawQuad(-4.5f, -0.5f, textureNearest);

    drawQuad(0.5f, 4.5f, textureLinear);

    glDisable(GL_TEXTURE_2D);

    glColor3f(1.0f, 1.0f, 1.0f);
    drawText(-3.2f, -2.5f, "GL_NEAREST");
    drawText(1.8f, -2.5f, "GL_LINEAR");

    glutSwapBuffers();
}

void reshape(int width, int height)
{
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(-5.0, 5.0, -3.0, 3.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void init()
{
    glClearColor(0.12f, 0.12f, 0.12f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-5.0, 5.0, -3.0, 3.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    createTextures();
}

void cleanup()
{
    glDeleteTextures(1, &textureNearest);
    glDeleteTextures(1, &textureLinear);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1000, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Q18 - Texture Filtering Comparison");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutCloseFunc(cleanup);

    glutMainLoop();

    return 0;
}