// Q15 [Hard] — Textured rotating cube
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

const int TEXTURE_SIZE = 64;

GLubyte textureImage[TEXTURE_SIZE][TEXTURE_SIZE][3];

GLuint textureID;

float rotateX = 0.0f;
float rotateY = 0.0f;

void generateTexture()
{
    for (int y = 0; y < TEXTURE_SIZE; y++)
    {
        for (int x = 0; x < TEXTURE_SIZE; x++)
        {
            int checker = ((x / 8) + (y / 8)) % 2;

            if (checker == 0)
            {
                textureImage[y][x][0] = 255;
                textureImage[y][x][1] = 100;
                textureImage[y][x][2] = 50;
            }
            else
            {
                textureImage[y][x][0] = 40;
                textureImage[y][x][1] = 150;
                textureImage[y][x][2] = 255;
            }
        }
    }
}

void createTexture()
{
    generateTexture();

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
        TEXTURE_SIZE,
        TEXTURE_SIZE,
        0,
        GL_RGB,
        GL_UNSIGNED_BYTE,
        textureImage
    );
}

void drawFace(
    float x1, float y1, float z1,
    float x2, float y2, float z2,
    float x3, float y3, float z3,
    float x4, float y4, float z4
)
{
    glBegin(GL_QUADS);

        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(x1, y1, z1);

        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(x2, y2, z2);

        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(x3, y3, z3);

        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(x4, y4, z4);

    glEnd();
}

// draw all six textured cube faces
void drawCube()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glColor3f(1.0f, 1.0f, 1.0f);

    // front face
    drawFace(
        -1, -1,  1,
         1, -1,  1,
         1,  1,  1,
        -1,  1,  1
    );

    // back face
    drawFace(
         1, -1, -1,
        -1, -1, -1,
        -1,  1, -1,
         1,  1, -1
    );

    // left face
    drawFace(
        -1, -1, -1,
        -1, -1,  1,
        -1,  1,  1,
        -1,  1, -1
    );

    // right face
    drawFace(
         1, -1,  1,
         1, -1, -1,
         1,  1, -1,
         1,  1,  1
    );

    // top face
    drawFace(
        -1,  1,  1,
         1,  1,  1,
         1,  1, -1,
        -1,  1, -1
    );

    // bottom face
    drawFace(
        -1, -1, -1,
         1, -1, -1,
         1, -1,  1,
        -1, -1,  1
    );

    glDisable(GL_TEXTURE_2D);
}

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

    glRotatef(rotateX, 1.0f, 0.0f, 0.0f);
    glRotatef(rotateY, 0.0f, 1.0f, 0.0f);

    drawCube();

    glutSwapBuffers();
}

void update(int value)
{
    rotateX += 0.5f;
    rotateY += 1.0f;

    if (rotateX >= 360.0f)
        rotateX -= 360.0f;

    if (rotateY >= 360.0f)
        rotateY -= 360.0f;

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

// configure the window and perspective
void reshape(int width, int height)
{
    if (height == 0)
        height = 1;

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45.0, (float)width / (float)height, 1.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
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

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(700, 600);
    glutInitWindowPosition(100, 100);

    glutCreateWindow("Q15 - Textured Rotating Cube");

    glClearColor(0.15f, 0.15f, 0.15f, 1.0f);

    glEnable(GL_DEPTH_TEST);

    createTexture();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    glutTimerFunc(16, update, 0);

    glutMainLoop();

    return 0;
}