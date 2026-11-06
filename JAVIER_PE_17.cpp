// Q17 [Hard] — Lit textured cube
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

float rotateX = 20.0f;
float rotateY = 30.0f;

void generateTexture()
{
    for (int y = 0; y < TEXTURE_SIZE; y++)
    {
        for (int x = 0; x < TEXTURE_SIZE; x++)
        {
            int checker = ((x / 8) + (y / 8)) % 2;

            if (checker == 0)
            {
                textureImage[y][x][0] = 220;
                textureImage[y][x][1] = 120;
                textureImage[y][x][2] = 40;
            }
            else
            {
                textureImage[y][x][0] = 50;
                textureImage[y][x][1] = 100;
                textureImage[y][x][2] = 220;
            }
        }
    }
}

void createTexture()
{
    generateTexture();

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

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

    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}

void drawFace(
    float nx, float ny, float nz,
    float x1, float y1, float z1,
    float x2, float y2, float z2,
    float x3, float y3, float z3,
    float x4, float y4, float z4
)
{
    glNormal3f(nx, ny, nz);

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

void drawCube()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // front face
    drawFace(
         0, 0, 1,
        -1, -1,  1,
         1, -1,  1,
         1,  1,  1,
        -1,  1,  1
    );

    // back face
    drawFace(
         0, 0, -1,
         1, -1, -1,
        -1, -1, -1,
        -1,  1, -1,
         1,  1, -1
    );

    // left face
    drawFace(
        -1, 0, 0,
        -1, -1, -1,
        -1, -1,  1,
        -1,  1,  1,
        -1,  1, -1
    );

    // right face
    drawFace(
         1, 0, 0,
         1, -1,  1,
         1, -1, -1,
         1,  1, -1,
         1,  1,  1
    );

    // top face
    drawFace(
         0, 1, 0,
        -1,  1,  1,
         1,  1,  1,
         1,  1, -1,
        -1,  1, -1
    );

    // bottom face
    drawFace(
         0, -1, 0,
        -1, -1, -1,
         1, -1, -1,
         1, -1,  1,
        -1, -1,  1
    );

    glDisable(GL_TEXTURE_2D);
}

void setupLighting()
{
    GLfloat lightPosition[] = {3.0f, 4.0f, 5.0f, 1.0f};

    GLfloat lightAmbient[] = {0.25f, 0.25f, 0.25f, 1.0f};
    GLfloat lightDiffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat lightSpecular[] = {1.0f, 1.0f, 1.0f, 1.0f};

    GLfloat materialAmbient[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat materialDiffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat materialSpecular[] = {0.4f, 0.4f, 0.4f, 1.0f};

    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);

    glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);

    glMaterialf(GL_FRONT, GL_SHININESS, 40.0f);
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

    setupLighting();

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
    glutCreateWindow("Q17 - Lit Textured Cube");
    glClearColor(0.12f, 0.12f, 0.12f, 1.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glEnable(GL_NORMALIZE);

    createTexture();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    glutTimerFunc(16, update, 0);

    glutMainLoop();

    return 0;
}