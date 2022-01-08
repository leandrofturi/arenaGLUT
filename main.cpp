#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <GL/freeglut.h>
#include "include/puppet.h"
#include <unistd.h>
#define INC_KEY 1
#define INC_KEYIDLE 0.01

// Key status
int keyStatus[256];

// Window dimensions
const GLint Width = 500;
const GLint Height = 500;

// Viewing dimensions
const GLint ViewingWidth = 500;
const GLint ViewingHeight = 500;

// Puppet motion
int animate = 0;

// Components
Puppet puppet;

void renderScene(void)
{
    // Clear the screen.
    glClear(GL_COLOR_BUFFER_BIT);

    puppet.draw();

    glutSwapBuffers(); // Draw the new frame of the game.
}

/*
void mouse(int button, int state, int x, int y)
{
    printf("%d\t%d\n", x, Height - y);
}
*/

void passiveMouseMotion(int x, int y)
{
    printf("%d %d\n", x, y);

    if (y < ViewingHeight / 2)
    {
        puppet.rotateArm(2);
    }
    else
    {
        puppet.rotateArm(-2);
    }

    if (x < ViewingWidth / 2)
    {
        puppet.setDirection(-1);
    }
    else
    {
        puppet.setDirection(1);
    }
}

void keyPress(unsigned char key, int x, int y)
{
    switch (key)
    {
    case '1':
        animate = !animate;
        break;
    case 'a':
    case 'A':
        keyStatus[(int)('a')] = 1; // Using keyStatus trick
        break;
    case 'd':
    case 'D':
        keyStatus[(int)('d')] = 1; // Using keyStatus trick
        break;
    case 27:
        exit(0);
    }
    glutPostRedisplay();
}

void keyup(unsigned char key, int x, int y)
{
    keyStatus[(int)(key)] = 0;
    glutPostRedisplay();
}

void ResetKeyStatus()
{
    int i;
    //Initialize keyStatus
    for (i = 0; i < 256; i++)
        keyStatus[i] = 0;
}

void init(void)
{
    ResetKeyStatus();
    // The color the windows will redraw. Its done to erase the previous frame.
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black, no opacity(alpha).

    glMatrixMode(GL_PROJECTION); // Select the projection matrix
    glOrtho(-(ViewingWidth / 2), // X coordinate of left edge
            (ViewingWidth / 2),  // X coordinate of right edge
            0.0,                 // Y coordinate of bottom edge
            ViewingHeight,       // Y coordinate of top edge
            -100,                // Z coordinate of the “near” plane
            100);                // Z coordinate of the “far” plane
    glMatrixMode(GL_MODELVIEW);  // Select the projection matrix
    glLoadIdentity();
}

void idle(void)
{
    double inc = INC_KEYIDLE;
    //Treat keyPress
    if (keyStatus[(int)('a')])
    {
        puppet.walkToLeft(inc);
    }
    if (keyStatus[(int)('d')])
    {
        puppet.walkToRight(inc);
    }

    //Control animation
    if (animate)
    {
        static int dir = 1;
        if (puppet.getX() > (ViewingWidth / 2))
        {
            dir *= -1;
        }
        else if (puppet.getX() < -(ViewingWidth / 2))
        {
            dir *= -1;
        }
        if (dir < 0)
        {
            puppet.walkToLeft(dir * INC_KEYIDLE);
        }
        else
        {
            puppet.walkToRight(dir * INC_KEYIDLE);
        }
    }

    glutPostRedisplay();
}

int main(int argc, char *argv[])
{
    // Initialize openGL with Double buffer and RGB color without transparency.
    // Its interesting to try GLUT_SINGLE instead of GLUT_DOUBLE.
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    // Create the window
    glutInitWindowSize(Width, Height);
    // glutInitWindowPosition(150, 50);
    glutCreateWindow("Arena GLUT");

    // Define callbacks
    glutDisplayFunc(renderScene);
    glutKeyboardFunc(keyPress);
    glutIdleFunc(idle);
    glutKeyboardUpFunc(keyup);
    glutPassiveMotionFunc(passiveMouseMotion);
    // glutMouseFunc(mouse);

    init();

    glutMainLoop();

    return 0;
}
