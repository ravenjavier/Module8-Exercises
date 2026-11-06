// Q07 [Easy] — Generate a texture ID
#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include <GL/freeglut.h>
using namespace std;

GLuint textureID = 0;

void init()
{
    // generate one texture ID
    glGenTextures(1, &textureID);

    cout << "Q07 - Generate a Texture ID" << endl;
    cout << "Generated Texture ID: " << textureID << endl;

    glBindTexture(GL_TEXTURE_2D, textureID);

    cout << "Texture successfully bound." << endl;

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(0.2f, 0.8f, 0.3f);
    glRasterPos2f(-0.5f, 0.2f);

    const char* message = "Texture ID Generated!";

    for (int i = 0; message[i] != '\0'; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, message[i]);
    }

    glutSwapBuffers();
}

void cleanup()
{
    if (textureID != 0)
    {
        glDeleteTextures(1, &textureID);
        cout << "Texture ID " << textureID << " deleted." << endl;
        textureID = 0;
    }
}

void keyboard(unsigned char key, int x, int y)
{
    if (key == 27)
    {
        cleanup();
        exit(0);
    }
}

void reshape(int width, int height)
{
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Q07 - Generate a Texture ID");

    init();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(reshape);

    glutMainLoop();

    return 0;
}