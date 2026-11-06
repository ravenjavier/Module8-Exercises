// Q20 [Hard] — Mini-scene integration
#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include <cmath>
#include <GL/freeglut.h>
using namespace std;

float rotationAngle = 0.0f;

GLuint floorTexture;
GLuint objectTexture;

const int TEX_SIZE = 64;

unsigned char floorData[TEX_SIZE][TEX_SIZE][3];
unsigned char objectData[TEX_SIZE][TEX_SIZE][3];

void createTextureData()
{
    // generate the checkerboard floor texture
    for (int y = 0; y < TEX_SIZE; y++)
    {
        for (int x = 0; x < TEX_SIZE; x++)
        {
            if (((x / 8) + (y / 8)) % 2 == 0)
            {
                floorData[y][x][0] = 180;
                floorData[y][x][1] = 180;
                floorData[y][x][2] = 180;
            }
            else
            {
                floorData[y][x][0] = 70;
                floorData[y][x][1] = 70;
                floorData[y][x][2] = 70;
            }

            // generate the colored object texture
            if (((x / 8) + (y / 8)) % 2 == 0)
            {
                objectData[y][x][0] = 230;
                objectData[y][x][1] = 100;
                objectData[y][x][2] = 30;
            }
            else
            {
                objectData[y][x][0] = 40;
                objectData[y][x][1] = 100;
                objectData[y][x][2] = 220;
            }
        }
    }
}

void createTextures()
{
    createTextureData();

    // create the floor texture
    glGenTextures(1, &floorTexture);
    glBindTexture(GL_TEXTURE_2D, floorTexture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(
        GL_TEXTURE_2D, 0, GL_RGB,
        TEX_SIZE, TEX_SIZE, 0,
        GL_RGB, GL_UNSIGNED_BYTE, floorData
    );

    glGenTextures(1, &objectTexture);
    glBindTexture(GL_TEXTURE_2D, objectTexture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(
        GL_TEXTURE_2D, 0, GL_RGB,
        TEX_SIZE, TEX_SIZE, 0,
        GL_RGB, GL_UNSIGNED_BYTE, objectData
    );

    glBindTexture(GL_TEXTURE_2D, 0);
}

void setupLighting()
{
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);

    GLfloat pointPosition[] = {-3.0f, 5.0f, 3.0f, 1.0f};
    GLfloat pointDiffuse[] = {1.0f, 0.85f, 0.7f, 1.0f};
    GLfloat pointSpecular[] = {1.0f, 1.0f, 1.0f, 1.0f};

    glLightfv(GL_LIGHT0, GL_POSITION, pointPosition);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, pointDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, pointSpecular);

    GLfloat directionalPosition[] = {1.0f, -1.0f, -1.0f, 0.0f};
    GLfloat directionalDiffuse[] = {0.35f, 0.4f, 0.8f, 1.0f};
    GLfloat directionalSpecular[] = {0.4f, 0.4f, 0.6f, 1.0f};

    glLightfv(GL_LIGHT1, GL_POSITION, directionalPosition);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, directionalDiffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, directionalSpecular);

    GLfloat ambient[] = {0.2f, 0.2f, 0.2f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);

    glEnable(GL_NORMALIZE);
}

void setMaterial()
{
    GLfloat ambient[] = {0.8f, 0.8f, 0.8f, 1.0f};
    GLfloat diffuse[] = {0.9f, 0.9f, 0.9f, 1.0f};
    GLfloat specular[] = {0.5f, 0.5f, 0.5f, 1.0f};

    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT, GL_SHININESS, 40.0f);
}

void drawFloor()
{
    glDisable(GL_LIGHTING);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, floorTexture);

    glColor3f(1.0f, 1.0f, 1.0f);

    glBegin(GL_QUADS);

        glNormal3f(0.0f, 1.0f, 0.0f);

        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-6.0f, -1.5f, -6.0f);

        glTexCoord2f(6.0f, 0.0f);
        glVertex3f(6.0f, -1.5f, -6.0f);

        glTexCoord2f(6.0f, 6.0f);
        glVertex3f(6.0f, -1.5f, 6.0f);

        glTexCoord2f(0.0f, 6.0f);
        glVertex3f(-6.0f, -1.5f, 6.0f);

    glEnd();

    glDisable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
}

void drawTexturedCube()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, objectTexture);
    glColor3f(1.0f, 1.0f, 1.0f);

    // front face
    glBegin(GL_QUADS);

        glNormal3f(0.0f, 0.0f, 1.0f);

        glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);

    // back face
        glNormal3f(0.0f, 0.0f, -1.0f);

        glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);

    // left face
        glNormal3f(-1.0f, 0.0f, 0.0f);

        glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);

    // right face
        glNormal3f(1.0f, 0.0f, 0.0f);

        glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);

    // top face
        glNormal3f(0.0f, 1.0f, 0.0f);

        glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);

    // bottom face
        glNormal3f(0.0f, -1.0f, 0.0f);

        glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, -1.0f, 1.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, -1.0f, 1.0f);

    glEnd();

    glDisable(GL_TEXTURE_2D);
}

void drawTexturedSphere()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, objectTexture);

    // draw the textured sphere
    glColor3f(1.0f, 1.0f, 1.0f);
    glutSolidSphere(1.0, 50, 50);

    glDisable(GL_TEXTURE_2D);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(
        7.0, 5.0, 10.0,
        0.0, 0.0, 0.0,
        0.0, 1.0, 0.0
    );

    setupLighting();
    setMaterial();

    drawFloor();

    // draw the rotating cube on the left
    glPushMatrix();
        glTranslatef(-2.5f, 0.0f, 0.0f);
        glRotatef(rotationAngle, 1.0f, 1.0f, 0.0f);
        setMaterial();
        drawTexturedCube();
    glPopMatrix();

    // draw the sphere on the right
    glPushMatrix();
        glTranslatef(2.5f, -0.5f, 0.0f);
        glRotatef(rotationAngle, 0.0f, 1.0f, 0.0f);
        setMaterial();
        drawTexturedSphere();
    glPopMatrix();

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
    createTextures();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1100, 700);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Q20 - Mini-Scene Integration");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(16, update, 0);

    glutMainLoop();

    return 0;
}