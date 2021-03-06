#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <iterator>
#include <list>
#include <chrono>
#include <GL/freeglut.h>
#include "include/puppet.h"
#include "include/gunshot.h"
#include "include/arena.h"
#include "include/collision.h"

#define INC_KEY 1
#define INC_KEYIDLE 0.01

// Key status
int keyStatus[256];
int mouseStatus[3];

// Window dimensions
const GLint Width = 500;
const GLint Height = 500;

// Viewing dimensions
const GLint ViewingWidth = 500;
const GLint ViewingHeight = 500;

// Components
Puppet puppet;
std::list<Block *> blocks;
std::list<Opponent *> opponents;
std::list<Gunshot *> gunshots;
Arena arena;

int atingido = 0;
static char str[1000];
void *font = GLUT_BITMAP_9_BY_15;
void ImprimePlacar(GLfloat x, GLfloat y)
{
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2f(x, y);
    const char *tmpWin = "Voce ganhou";
    const char *tmpLose = "Voce perdeu";
    const char *tmpStr;
    if (puppet.isAlive())
    {
        tmpStr = tmpWin;
    }
    else
    {
        tmpStr = tmpLose;
    }
    while (*tmpStr)
    {
        glutBitmapCharacter(font, *tmpStr);
        tmpStr++;
    }
}

void renderScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    puppet.draw();

    for (std::list<Block *>::iterator it = blocks.begin(); it != blocks.end(); ++it)
    {
        (*it)->draw();
    }

    for (std::list<Opponent *>::iterator it = opponents.begin(); it != opponents.end(); ++it)
    {
        (*it)->draw();
        for (std::list<Gunshot *>::iterator gs = (*it)->gunshots.begin(); gs != (*it)->gunshots.end(); ++gs)
        {
            (*gs)->draw();
        }
    }

    for (std::list<Gunshot *>::iterator it = gunshots.begin(); it != gunshots.end(); ++it)
    {
        (*it)->draw();
    }

    if (atingido)
    {
        ImprimePlacar(puppet.getX() - 8, puppet.getY() - puppet.getHeight() * 1.5);
    }

    glutSwapBuffers(); // Draw the new frame of the game.
}

void mouse(int button, int state, int x, int y)
{
    if (!atingido)
    {
        if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        {
            gunshots.push_back(puppet.shoot());
        }
        if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && !puppet.isFlying())
        {
            mouseStatus[2] = 1;
        }
        if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP)
        {
            mouseStatus[2] = 0;
            puppet.shootDown();
        }
        glutPostRedisplay();
    }
}

void passiveMouseMotion(int x, int y)
{
    if (!atingido)
    {
        if (y > ViewingHeight / 2)
        {
            puppet.rotateArm(2);
        }
        else
        {
            puppet.rotateArm(-2);
        }

        if (x < ViewingWidth / 2 && (!keyStatus[(int)('d')]))
        {
            puppet.setDirection(-1);
        }
        else if (!keyStatus[(int)('a')])
        {
            puppet.setDirection(1);
        }
    }
}

void keyPress(unsigned char key, int x, int y)
{
    GLfloat hr = arena.getHeight();
    GLfloat scaler = (ViewingHeight - hr) / hr + 1.0;

    if (!atingido)
    {
        switch (key)
        {
        case 'a':
        case 'A':
            keyStatus[(int)('a')] = 1; // Using keyStatus trick
            puppet.setDirection(-1);
            break;
        case 'd':
        case 'D':
            keyStatus[(int)('d')] = 1; // Using keyStatus trick
            puppet.setDirection(1);
            break;
        case 27:
            exit(0);
        }
        glutPostRedisplay();
    }
    else
    {
        switch (key)
        {
        case 'r':
        case 'R':
            puppet.reset();
            for (std::list<Gunshot *>::iterator it = gunshots.begin(); it != gunshots.end();)
            {
                it = gunshots.erase(it);
            }

            for (std::list<Opponent *>::iterator it = opponents.begin(); it != opponents.end(); ++it)
            {
                //(*it)->reset();
                for (std::list<Gunshot *>::iterator gs = (*it)->gunshots.begin(); gs != (*it)->gunshots.end();)
                {
                    gs = (*it)->gunshots.erase(gs);
                }
            }
            atingido = 0;
            glLoadIdentity();
            glTranslatef(-puppet.getX() * scaler + ViewingHeight / 2.0, 0.0, 0.0);
            glScalef(scaler, scaler, scaler);

            break;
        case 27:
            exit(0);
        }
        glutPostRedisplay();
    }
}

void keyup(unsigned char key, int x, int y)
{
    keyStatus[(int)(key)] = 0;
    glutPostRedisplay();
}

void ResetKeyStatus()
{
    int i;
    // Initialize keyStatus
    for (i = 0; i < 256; i++)
        keyStatus[i] = 0;

    // Mouse
    mouseStatus[0] = 0;
    mouseStatus[1] = 0;
    mouseStatus[2] = 0;
}

void opponentShot(int time)
{
    if (!atingido)
    {
        int i = (int)(rand() % opponents.size());
        std::list<Opponent *>::iterator it = opponents.begin();
        std::advance(it, i);
        (*it)->shot(puppet.getX(), puppet.getY());

        glutTimerFunc(500, opponentShot, 0.0);
    }
}

void opponentMove(int time)
{
    if (!atingido)
    {
        for (std::list<Opponent *>::iterator it = opponents.begin(); it != opponents.end(); ++it)
        {
            (*it)->move();
        }

        glutTimerFunc(100, opponentMove, 0.0);
    }
}

void init(void)
{
    ResetKeyStatus();
    // The color the windows will redraw. Its done to erase the previous frame.
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // Black, no opacity(alpha).

    glShadeModel(GL_SMOOTH);
    glEnable(GL_CULL_FACE);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glViewport (0, 0, (GLsizei) Width, 
            (GLsizei) Height);

    glMatrixMode(GL_PROJECTION); // Select the projection matrix
    glOrtho(0.0,                 // X coordinate of left edge
            ViewingWidth,        // X coordinate of right edge
            ViewingHeight,       // Y coordinate of bottom edge
            0.0,                 // Y coordinate of top edge
            -100,                // Z coordinate of the ???near??? plane
            100);                // Z coordinate of the ???far??? plane
    glMatrixMode(GL_MODELVIEW);  // Select the projection matrix

    glLoadIdentity();
}

void idle(void)
{
    if (!atingido)
    {
        if (!puppet.isAlive())
        {
            atingido = 1;
        }

        double inc = INC_KEYIDLE;

        if (puppet.getX() + puppet.getSpeed() * inc >= arena.getWidth())
        {
            atingido = 1;
        }

        if (keyStatus[(int)('a')])
        {
            if ((puppet.getDirection() == -1) && puppet.walk(-inc))
            {
                glTranslatef(puppet.getSpeed() * inc, 0.0, 0.0);
            }
        }
        if (keyStatus[(int)('d')])
        {
            if ((puppet.getDirection() == 1) && puppet.walk(inc))
            {
                glTranslatef(-puppet.getSpeed() * inc, 0.0, 0.0);
            }
        }
        if (mouseStatus[2])
        {
            puppet.fly();
        }

        for (std::list<Gunshot *>::iterator it = gunshots.begin(); it != gunshots.end();)
        {
            (*it)->move();
            if (!(*it)->valid())
            {
                it = gunshots.erase(it);
            }
            else
            {
                ++it;
            }
        }

        for (std::list<Opponent *>::iterator it = opponents.begin(); it != opponents.end(); ++it)
        {
            for (std::list<Gunshot *>::iterator gs = (*it)->gunshots.begin(); gs != (*it)->gunshots.end();)
            {
                (*gs)->move();
                if (!(*gs)->valid())
                {
                    gs = (*it)->gunshots.erase(gs);
                }
                else
                {
                    ++gs;
                }
            }
        }

        puppet.gravity();
        Collision::handleCollision(&puppet, blocks, &opponents, &gunshots);

        glutPostRedisplay();
    }
}

int main(int argc, char *argv[])
{
    char *pathArena = (char *)malloc(256);
    strcpy(pathArena, argv[1]);

    // Initialize openGL with Double buffer and RGB color without transparency.
    // Its interesting to try GLUT_SINGLE instead of GLUT_DOUBLE.
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    // Create the window
    glutInitWindowSize(Width, Height);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Arena GLUT");

    // Define callbacks
    glutDisplayFunc(renderScene);
    glutKeyboardFunc(keyPress);
    glutIdleFunc(idle);
    glutKeyboardUpFunc(keyup);
    glutMouseFunc(mouse);
    glutPassiveMotionFunc(passiveMouseMotion);

    glutTimerFunc(500, opponentShot, 0.0);
    glutTimerFunc(100, opponentMove, 0.0);

    init();

    // Arena
    arena.loadScenario(pathArena);
    arena.loadElements(&blocks, &opponents, &puppet, ViewingWidth, ViewingHeight);

    GLfloat h = arena.getHeight();

    GLfloat scale = (ViewingHeight - h) / h + 1.0;
    glTranslatef(-puppet.getX() * scale + ViewingHeight / 2.0, 0.0, 0.0);
    glScalef(scale, scale, scale);

    glutMainLoop();

    free(pathArena);

    return 0;
}
