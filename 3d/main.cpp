#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include "include/imageloader.h"
#include "include/puppet.h"
#include "include/arena.h"
#include "include/collision.h"

Arena arena;
Puppet puppet;

// Key status
#define INC_KEYIDLE 1
int keyStatus[256];

// Viewing dimensions
const GLint ViewingWidth = 500;
const GLint ViewingHeight = 500;

// Identificadores de textura
GLuint texturePlane;

int nigth = 0;
int ghost = 1;
int endGame = 0;

// Camera controls
double camDist = 50;
double camXYAngle = 0;
double camXZAngle = 0;
int toggleCam = 0;
int camAngle = 60;
int lastX = 0;
int lastY = 0;
int buttonDown = 0;

int sign(GLfloat x)
{
    return (x > 0) - (x < 0);
}

GLuint LoadTextureRAW(const char *filename)
{
    GLuint texture;

    Image *image = loadBMP(filename);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    //    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_REPLACE );
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D,               //Always GL_TEXTURE_2D
                 0,                           //0 for now
                 GL_RGB,                      //Format OpenGL uses for image
                 image->width, image->height, //Width and height
                 0,                           //The border of the image
                 GL_RGB,                      //GL_RGB, because pixels are stored in RGB format
                 GL_UNSIGNED_BYTE,            //GL_UNSIGNED_BYTE, because pixels are stored
                                              //as unsigned numbers
                 image->pixels);              //The actual pixel data
    delete image;

    return texture;
}

void RasterChars(GLfloat x, GLfloat y, GLfloat z, const char *text, double r, double g, double b)
{
    // Push to recover original attributes
    glPushAttrib(GL_ENABLE_BIT);
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    //Draw text in the x, y, z position
    glColor3f(r, g, b);
    glRasterPos3f(x, y, z);
    const char *tmpStr;
    tmpStr = text;
    while (*tmpStr)
    {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *tmpStr);
        tmpStr++;
    }
    glPopAttrib();
}

void PrintText(GLfloat x, GLfloat y, const char *text, double r, double g, double b)
{
    //Draw text considering a 2D space(disable all 3d features)
    glMatrixMode(GL_PROJECTION);
    //Push to recover original PROJECTION MATRIX
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, 1, 0, 1, -1, 1);
    RasterChars(x, y, 0, text, r, g, b);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

void DrawAxes()
{
    GLfloat color_r[] = {1.0, 0.0, 0.0, 1.0};
    GLfloat color_g[] = {0.0, 1.0, 0.0, 1.0};
    GLfloat color_b[] = {0.0, 0.0, 1.0, 1.0};

    glPushAttrib(GL_ENABLE_BIT);
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);

    glPushMatrix();
    glTranslatef(puppet.getX(), puppet.getY(), puppet.getZ());

    //x axis
    glPushMatrix();
    glColor3fv(color_r);
    glScalef(5, 0.3, 0.3);
    glTranslatef(0.5, 0, 0); // put in one end
    glutSolidCube(1.0);
    glPopMatrix();

    //y axis
    glPushMatrix();
    glColor3fv(color_g);
    glRotatef(90, 0, 0, 1);
    glScalef(5, 0.3, 0.3);
    glTranslatef(0.5, 0, 0); // put in one end
    glutSolidCube(1.0);
    glPopMatrix();

    //z axis
    glPushMatrix();
    glColor3fv(color_b);
    glRotatef(-90, 0, 1, 0);
    glScalef(5, 0.3, 0.3);
    glTranslatef(0.5, 0, 0); // put in one end
    glutSolidCube(1.0);
    glPopMatrix();

    glPopMatrix();

    glPopAttrib();
}

void DisplayPlane(GLuint texture)
{
    GLfloat materialEmission[] = {1.0, 1.0, 1.0, 1};
    GLfloat materialColorA[] = {0.2, 0.2, 0.2, 1};
    GLfloat materialColorD[] = {1.0, 1.0, 1.0, 1};
    GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1};
    GLfloat mat_shininess[] = {100.0};
    glColor3f(1, 1, 1);

    glMaterialfv(GL_FRONT, GL_EMISSION, materialEmission);
    glMaterialfv(GL_FRONT, GL_AMBIENT, materialColorA);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, materialColorD);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //X
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); //Y

    glBindTexture(GL_TEXTURE_2D, texture);
    double textureS = 1; // Bigger than 1, repeat
    glBegin(GL_QUADS);
    glNormal3f(0, 1, 0);
    glTexCoord2f(0, 0);
    glVertex3f(-1, 0, -1);
    glNormal3f(0, 1, 0);
    glTexCoord2f(0, textureS);
    glVertex3f(-1, 0, +1);
    glNormal3f(0, 1, 0);
    glTexCoord2f(textureS, textureS);
    glVertex3f(+1, 0, +1);
    glNormal3f(0, 1, 0);
    glTexCoord2f(textureS, 0);
    glVertex3f(+1, 0, -1);
    glEnd();
}

void display(void)
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    if (endGame)
        PrintText(0.1, 0.1, "Voce perdeu", 0, 1, 0);
    if (toggleCam == 0)
    {
        if (endGame)
            PrintText(0.1, 0.1, "Voce perdeu", 0, 1, 0);
        else
            PrintText(0.1, 0.1, "Movable Camera", 0, 1, 0);
        glTranslatef(0.0, -puppet.getHeight(), -camDist);
        glRotatef(camXZAngle, 1, 0, 0);
        glRotatef(camXYAngle, 0, 1, 0);
        glTranslatef(-puppet.getX(), -puppet.getY(), -puppet.getZ());
    }
    else if (toggleCam == 1)
    {
        if (endGame)
            PrintText(0.1, 0.1, "Voce perdeu", 0, 1, 0);
        else
            PrintText(0.1, 0.1, "Static Camera at a Distance", 0, 1, 0);
        gluLookAt(arena.getHeight() / 2.0 + camDist * 2.0, arena.getHeight() * 1.5, puppet.getZ(),
                  arena.getHeight() / 2.0, arena.getHeight() * 1.5, puppet.getZ(),
                  0, 1, 0);
    }
    else if (toggleCam == 2)
    {
        if (endGame)
            PrintText(0.1, 0.1, "Voce perdeu", 0, 1, 0);
        else
            PrintText(0.1, 0.1, "Eye Camera", 0, 1, 0);
        glTranslatef(-1.0, -puppet.getHeight() * 0.8, -puppet.getDepth() / 2.0);
        glRotatef(camXZAngle + 8.0, 1, 0, 0);
        glRotatef(camXYAngle, 0, 1, 0);
        gluLookAt(
            puppet.getX(), puppet.getY(), puppet.getZ(),
            puppet.getX(), puppet.getY(), puppet.getZ() - camDist,
            0.0, 1.0, 0.0);
    }
    else if (toggleCam == 3)
    {
        if (endGame)
            PrintText(0.1, 0.1, "Voce perdeu", 0, 1, 0);
        else
            PrintText(0.1, 0.1, "Arm Camera", 0, 1, 0);
        glTranslatef(-4.0 * puppet.getWidth(), -puppet.getHeight() * 0.8, -puppet.getDepth() / 2.0);
        glRotatef(camXZAngle + 8.0, 1, 0, 0);
        glRotatef(camXYAngle, 0, 1, 0);
        gluLookAt(
            puppet.getArmZ(), puppet.getArmY(), puppet.getArmX(),
            puppet.getArmZ(), puppet.getArmY(), puppet.getArmX() - camDist,
            0.0, 1.0, 0.0);
    }

    if (!nigth)
    {
        GLfloat light_position[] = {puppet.getX(), puppet.getY() + puppet.getHeight(), puppet.getZ(), 1.0};
        glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    }
    else
    {
        GLfloat light_position[] = {puppet.getX(), puppet.getY() + puppet.getHeight(), puppet.getZ(), 1.0};
        glLightfv(GL_LIGHT0, GL_POSITION, light_position);
        GLfloat light_direction[] = {0.0, -1.0, 0.0, 1.0};
        glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light_direction);
        GLfloat cutoff = 50.0;
        glLightfv(GL_LIGHT0, GL_SPOT_CUTOFF, &cutoff);
    }
    glEnable(GL_LIGHT0);

    glPushMatrix();
    glTranslatef(0.0, arena.getHeight(), 0.0);
    glScalef(arena.getHeight() / 2.0, 1.0, arena.getWidth());
    // DisplayPlane(texturePlane);
    glPopMatrix();

    // DrawAxes();
    glPushMatrix();
    puppet.draw();
    glPopMatrix();

    glPushMatrix();
    arena.draw();
    glPopMatrix();

    glutSwapBuffers();
}
void init(char *pathArena)
{
    // Initialize keyStatus
    for (int i = 0; i < 256; i++)
        keyStatus[i] = 0;

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
    glShadeModel(GL_SMOOTH);

    glDepthFunc(GL_LEQUAL);

    texturePlane = LoadTextureRAW("img/stars1.bmp");

    arena.init(pathArena);
    puppet.init();
    arena.load(&puppet);

    // Scale for the arena height
    // GLfloat h = arena.getHeight();
    // GLfloat scale = (ViewingHeight - h) / h + 1.0;
    // glTranslatef(-puppet.getX() * scale + ViewingHeight / 2.0, 0.0, 0.0);
    // glScalef(scale, scale, scale);

    glEnable(GL_LIGHT0);
}

void changeCamera(int angle, int w, int h)
{
    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    gluPerspective(angle,
                   (GLfloat)w / (GLfloat)h, 1, 150.0);

    glMatrixMode(GL_MODELVIEW);
}

void reshape(int w, int h)
{

    glViewport(0, 0, (GLsizei)w, (GLsizei)h);

    changeCamera(camAngle, w, h);
}

void mouseCallback(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        lastX = x;
        lastY = y;
        buttonDown = 1;
    }
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
    {
        buttonDown = 0;
    }
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        arena.gunshots.push_back(puppet.shoot());
    }
}

void mouseMotion(int x, int y)
{
    if (!buttonDown)
        return;

    camXYAngle += x - lastX;
    camXZAngle += y - lastY;

    camXYAngle = (int)camXYAngle % 360;
    camXZAngle = (int)camXZAngle % 360;

    camXYAngle = fabs(camXYAngle) > 45 ? 45 * sign(camXYAngle) : camXYAngle;
    camXZAngle = fabs(camXZAngle) > 45 ? 45 * sign(camXZAngle) : camXZAngle;

    lastX = x;
    lastY = y;
}

void passiveMouseMotion(int x, int y)
{
    if (y > ViewingHeight / 2)
    {
        puppet.rotateArm(-2);
    }
    else
    {
        puppet.rotateArm(+2);
    }
}

void idle()
{
    if (!puppet.isAlive() && !ghost)
    {
        endGame = 1;
        return;
    }

    double inc = INC_KEYIDLE;

    bool bump = Collision::collision(&puppet, &arena);

    if (keyStatus[(int)('a')])
    {
        camXYAngle -= (int)inc % 360;
        camXYAngle = fabs(camXYAngle) > 45 ? 45 * sign(camXYAngle) : camXYAngle;
        puppet.rotate(-inc);
    }
    if (keyStatus[(int)('d')])
    {
        camXYAngle += (int)inc % 360;
        camXYAngle = fabs(camXYAngle) > 45 ? 45 * sign(camXYAngle) : camXYAngle;
        puppet.rotate(inc);
    }
    if (puppet.isElevated() && !puppet.bumpOpponent())
    {
        if (keyStatus[(int)('w')])
        {
            puppet.walk(bump ? -inc : inc);
        }
        if (keyStatus[(int)('s')])
        {
            puppet.walk(bump ? inc : -inc);
        }
    }
    else
    {
        if (keyStatus[(int)('w')])
        {
            puppet.walk(bump ? inc : -inc);
        }
        if (keyStatus[(int)('s')])
        {
            puppet.walk(bump ? -inc : inc);
        }
    }

    if (keyStatus[(int)(' ')] && (!bump || puppet.isElevated()))
    {
        puppet.jump(inc);
    }
    else
    {
        puppet.handleGravity();
    }
    arena.move();
    arena.opponentRotate(&puppet);
    arena.handleGravity();

    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
    static bool textureEnebled = true;
    static bool lightingEnebled = true;
    static bool smoothEnebled = true;
    switch (key)
    {
    case 'G': // modo fatasma: n morre e n tem limite
        ghost = !ghost;
        puppet.ghost(ghost);
        break;
    case '1': // camera
        toggleCam = 0;
        arena.cam = 0;
        break;
    case '2': // camera
        toggleCam = 1;
        arena.cam = 1;
        break;
    case '3': // camera
        toggleCam = 2;
        arena.cam = 2;
        break;
    case '4': // camera
        toggleCam = 3;
        arena.cam = 3;
        break;
    case 'a': // moviment
        keyStatus[(int)('a')] = 1;
        break;
    case 'd': // moviment
        keyStatus[(int)('d')] = 1;
        break;
    case 'w': // moviment
        keyStatus[(int)('w')] = 1;
        break;
    case 's': // moviment
        keyStatus[(int)('s')] = 1;
        break;
    case ' ': // junp
        keyStatus[(int)(' ')] = 1;
        break;
    case 't': // texture
        if (textureEnebled)
        {
            glDisable(GL_TEXTURE_2D);
            arena.cam = 1;
        }
        else
        {
            glEnable(GL_TEXTURE_2D);
            arena.cam = toggleCam;
        }
        textureEnebled = !textureEnebled;
        break;
    case 'l': // light
        if (lightingEnebled)
        {
            glDisable(GL_LIGHTING);
        }
        else
        {
            glEnable(GL_LIGHTING);
        }
        lightingEnebled = !lightingEnebled;
        break;
    case 'S': // smooth
        if (smoothEnebled)
        {
            glShadeModel(GL_FLAT);
        }
        else
        {
            glShadeModel(GL_SMOOTH);
        }
        smoothEnebled = !smoothEnebled;
        break;
    case 'N':
        nigth = !nigth;
        break;
    case '+': // zoom
    {
        int inc = camAngle >= 180 ? 0 : 1;
        camAngle += inc;
        changeCamera(camAngle,
                     glutGet(GLUT_WINDOW_WIDTH),
                     glutGet(GLUT_WINDOW_HEIGHT));
        break;
    }
    case '-': // zoom
    {
        int inc = camAngle <= 5 ? 0 : 1;
        camAngle -= inc;
        changeCamera(camAngle, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
        break;
    }
    case 'A': // anima????o
        if (puppet.canAnimate)
        {
            if (puppet.isActing())
                break;
            puppet.kick();
        }
        break;
    case 'P': // anima????o
        if (puppet.canAnimate)
        {
            if (puppet.isActing())
                break;
            puppet.punch();
        }
        break;
    case 'D': // anima????o
        if (puppet.canAnimate)
        {
            if (puppet.isActing())
                break;
            puppet.dance();
        }
        break;
    case '0': // habilitar anima????o
        if (puppet.canAnimate)
            puppet.animate();
        break;
    case 27:
        exit(0);
        break;
    }
}

void keyup(unsigned char key, int x, int y)
{
    keyStatus[(int)(key)] = 0;
    glutPostRedisplay();
}

void opponentShot(int time)
{
    arena.opponentShot(&puppet);
    if (!endGame)
        glutTimerFunc(500, opponentShot, 0.0);
}

void opponentMove(int time)
{
    arena.opponentMove();
    if (!endGame)
        glutTimerFunc(100, opponentMove, 0.0);
}

int main(int argc, char **argv)
{
    char *pathArena = (char *)malloc(256);
    strcpy(pathArena, argv[1]);

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);

    glutInitWindowSize(500, 500);

    glutInitWindowPosition(0, 0);

    glutCreateWindow("Arena Glut");

    init(pathArena);

    glutDisplayFunc(idle);

    glutIdleFunc(display);

    glutReshapeFunc(reshape);

    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyup);

    glutMotionFunc(mouseMotion);
    glutMouseFunc(mouseCallback);
    glutPassiveMotionFunc(passiveMouseMotion);

    glutTimerFunc(500, opponentShot, 0.0);
    glutTimerFunc(100, opponentMove, 0.0);

    glutMainLoop();

    return 0;
}
