#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include "include/imageloader.h"
#include "include/puppet.h"
#include "include/arena.h"

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

// Camera controls
double camDist = 50;
double camXYAngle = 0;
double camXZAngle = 0;
int toggleCam = 0;
int camAngle = 60;
int lastX = 0;
int lastY = 0;
int buttonDown = 0;

// Cotroles de giro
double anglePuppet = 0;

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

    if (toggleCam == 0)
    {
        PrintText(0.1, 0.1, "Movable Camera", 0, 1, 0);
        glTranslatef(0.0, 0.0, -camDist);
        glRotatef(camXZAngle, 1, 0, 0);
        glRotatef(camXYAngle, 0, 1, 0);
        glTranslatef(-puppet.getX(), -puppet.getY(), -puppet.getZ());
    }
    else if (toggleCam == 1)
    {
        PrintText(0.1, 0.1, "Static Camera at a Distance", 0, 1, 0);
        gluLookAt(arena.getWidth() / 2.0, arena.getHeight() / 2.0, 50, 0, 0, 0, 0, 1, 0);
    }
    else if (toggleCam == 2)
    {
        PrintText(0.1, 0.1, "Puppet Camera", 0, 1, 0);
        gluLookAt(puppet.getX(), puppet.getY(), puppet.getZ(), -sin(anglePuppet / 180 * M_PI), 0, -cos(anglePuppet / 180 * M_PI), 0, 1, 0);
    }

    GLfloat light_position[] = {puppet.getX(), puppet.getY(), puppet.getZ(), 1.0};
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glPushMatrix();
    glScalef(70, 70, 1);
    glTranslatef(0, 0, -12);
    glRotatef(90, 1, 0, 0);
    // DisplayPlane(texturePlane);
    glPopMatrix();


    if (toggleCam != 2)
    {
        DrawAxes();
        glPushMatrix();
        puppet.draw();
        glPopMatrix();
    }

    glPushMatrix();
    glRotatef(anglePuppet, 0, 1, 0);
    arena.draw();
    glPopMatrix();

    glutSwapBuffers();
}
void init(void)
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

    arena.init("input/arena_teste.svg");
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

void mouse_callback(int button, int state, int x, int y)
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
}

void mouse_motion(int x, int y)
{
    if (!buttonDown)
        return;

    camXYAngle += x - lastX;
    camXZAngle += y - lastY;

    camXYAngle = (int)camXYAngle % 360;
    camXZAngle = (int)camXZAngle % 360;

    lastX = x;
    lastY = y;
}

void idle()
{
    double inc = INC_KEYIDLE;

    if (keyStatus[(int)('a')])
    {
        camXYAngle -= (int)inc % 360;
        puppet.rotate(-inc);
    }
    if (keyStatus[(int)('d')])
    {
        camXYAngle += (int)inc % 360;
        puppet.rotate(inc);
        // camXZAngle += inc;
    }
    if (keyStatus[(int)('w')])
    {
        puppet.walk(-inc);
    }
    if (keyStatus[(int)('s')])
    {
        puppet.walk(inc);
    }
    if (keyStatus[(int)(' ')])
    {
        puppet.jump(inc);
    }
    else
    {
        puppet.handleGravity();
    }
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
    static bool textureEnebled = true;
    static bool lightingEnebled = true;
    static bool smoothEnebled = true;
    switch (key)
    {
    case '1':
        toggleCam = 0;
        break;
    case '2':
        toggleCam = 1;
        break;
    case '3':
        toggleCam = 2;
        break;
    case 'a':
        keyStatus[(int)('a')] = 1;
        break;
    case 'd':
        keyStatus[(int)('d')] = 1;
        break;
    case 'w':
        keyStatus[(int)('w')] = 1;
        break;
    case 's':
        keyStatus[(int)('s')] = 1;
        break;
    case ' ':
        keyStatus[(int)(' ')] = 1;
        break;
    case 't':
        if (textureEnebled)
        {
            glDisable(GL_TEXTURE_2D);
        }
        else
        {
            glEnable(GL_TEXTURE_2D);
        }
        textureEnebled = !textureEnebled;
        break;
    case 'l':
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
    case 'S':
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
    case '+':
    {
        int inc = camAngle >= 180 ? 0 : 1;
        camAngle += inc;
        changeCamera(camAngle,
                     glutGet(GLUT_WINDOW_WIDTH),
                     glutGet(GLUT_WINDOW_HEIGHT));
        break;
    }
    case '-':
    {
        int inc = camAngle <= 5 ? 0 : 1;
        camAngle -= inc;
        changeCamera(camAngle, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
        break;
    }
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

int main(int argc, char **argv)
{

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);

    glutInitWindowSize(500, 500);

    glutInitWindowPosition(0, 0);

    glutCreateWindow("Arena Glut");

    init();

    glutDisplayFunc(idle);

    glutIdleFunc(display);

    glutReshapeFunc(reshape);

    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyup);

    glutMotionFunc(mouse_motion);
    glutMouseFunc(mouse_callback);

    glutMainLoop();

    return 0;
}
