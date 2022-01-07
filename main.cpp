#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <GL/freeglut.h>
#include "include/boneco.h"
#include "include/alvo.h"
#define INC_KEY 1
#define INC_KEYIDLE 0.01

//Key status
int keyStatus[256];

// Window dimensions
const GLint Width = 700;
const GLint Height = 700;

// Viewing dimensions
const GLint ViewingWidth = 500;
const GLint ViewingHeight = 500;

//Controla a animacao do boneco
int animate = 0;

// Componentes do mundo virtual sendo modelado
Boneco boneco;     // Um boneco
Tiro *tiro = NULL; // Um tiro por vez
Alvo alvo(0, 200); // Um alvo por vez

int atingido = 0;
static char str[1000];
void *font = GLUT_BITMAP_9_BY_15;
void ImprimePlacar(GLfloat x, GLfloat y)
{
    glColor3f(1.0, 1.0, 1.0);
    // Cria a string a ser impressa
    char *tmpStr;
    sprintf(str, "Atingido: %d", atingido);
    // Define a posicao onde vai comecar a imprimir
    glRasterPos2f(x, y);
    // Imprime um caractere por vez
    tmpStr = str;
    while (*tmpStr)
    {
        glutBitmapCharacter(font, *tmpStr);
        tmpStr++;
    }
}

void renderScene(void)
{
    // Clear the screen.
    glClear(GL_COLOR_BUFFER_BIT);

    boneco.Desenha();

    if (tiro)
        tiro->Desenha();

    alvo.Desenha();
    ImprimePlacar(-(ViewingWidth / 2)+30,
                  -(ViewingWidth / 2)+30);

    glutSwapBuffers(); // Desenha the new frame of the game.
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
    case 'f':
    case 'F':
        boneco.RodaBraco1(-INC_KEY); // Without keyStatus trick
        break;
    case 'r':
    case 'R':
        boneco.RodaBraco1(+INC_KEY); // Without keyStatus trick
        break;
    case 'g':
    case 'G':
        boneco.RodaBraco2(-INC_KEY); // Without keyStatus trick
        break;
    case 't':
    case 'T':
        boneco.RodaBraco2(+INC_KEY); // Without keyStatus trick
        break;
    case 'h':
    case 'H':
        boneco.RodaBraco3(-INC_KEY); // Without keyStatus trick
        break;
    case 'y':
    case 'Y':
        boneco.RodaBraco3(+INC_KEY); // Without keyStatus trick
        break;
    case ' ':
        if (!tiro)
            tiro = boneco.Atira();
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

    glMatrixMode(GL_PROJECTION);  // Select the projection matrix
    glOrtho(-(ViewingWidth / 2),  // X coordinate of left edge
            (ViewingWidth / 2),   // X coordinate of right edge
            -(ViewingHeight / 2), // Y coordinate of bottom edge
            (ViewingHeight / 2),  // Y coordinate of top edge
            -100,                 // Z coordinate of the “near” plane
            100);                 // Z coordinate of the “far” plane
    glMatrixMode(GL_MODELVIEW);   // Select the projection matrix
    glLoadIdentity();
}

void idle(void)
{
    // for(int i = 0; i < 90000000; i++);
    static GLdouble previousTime = glutGet(GLUT_ELAPSED_TIME);
    GLdouble currentTime, timeDiference;

    double inc = INC_KEYIDLE;
    //Treat keyPress
    if (keyStatus[(int)('a')])
    {
        boneco.MoveEmX(-inc);
    }
    if (keyStatus[(int)('d')])
    {
        boneco.MoveEmX(inc);
    }

    //Pega o tempo que passou do inicio da aplicacao
    currentTime = glutGet(GLUT_ELAPSED_TIME);
    // Calcula o tempo decorrido desde de a ultima frame.
    timeDiference = currentTime - previousTime;

    //Trata o tiro (soh permite um tiro por vez)
    //Poderia usar uma lista para tratar varios tiros
    if (tiro)
    {
        tiro->Move(timeDiference);

        //Trata colisao
        if (alvo.Atingido(tiro))
        {
            alvo.Recria(rand() % 500 - 250, 200);
            atingido ++;
            
            delete tiro;
            tiro = NULL;
        }

        if (tiro && !tiro->Valido())
        {
            delete tiro;
            tiro = NULL;
        }
    }

    //Control animation
    if (animate)
    {
        static int dir = 1;
        if (boneco.ObtemX() > (ViewingWidth / 2))
        {
            dir *= -1;
        }
        else if (boneco.ObtemX() < -(ViewingWidth / 2))
        {
            dir *= -1;
        }
        boneco.MoveEmX(dir * INC_KEYIDLE);
    }

    glutPostRedisplay();

    //Atualiza o tempo do ultimo frame ocorrido
    previousTime = currentTime;
}

int main(int argc, char *argv[])
{
    // Initialize openGL with Double buffer and RGB color without transparency.
    // Its interesting to try GLUT_SINGLE instead of GLUT_DOUBLE.
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    // Create the window.
    glutInitWindowSize(Width, Height);
    glutInitWindowPosition(150, 50);
    glutCreateWindow("Tranformations 2D");

    // Define callbacks.
    glutDisplayFunc(renderScene);
    glutKeyboardFunc(keyPress);
    glutIdleFunc(idle);
    glutKeyboardUpFunc(keyup);

    init();

    glutMainLoop();

    return 0;
}
