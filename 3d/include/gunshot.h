#ifndef GUNSHOT_H
#define GUNSHOT_H
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include "geometries.h"
#include "imageloader.h"

class Gunshot
{
    GLfloat radiusGunshot = 1;
    GLfloat gXInit;
    GLfloat gYInit;
    GLfloat gZInit;
    GLfloat gX;
    GLfloat gY;
    GLfloat gZ;
    GLfloat gDirectionAng;
    GLfloat gSpeed;
    GLfloat gR;
    GLfloat gG;
    GLfloat gB;
    GLuint textureGunshot;

    OBJ *head;

public:
    Gunshot(GLfloat x, GLfloat y, GLfloat z, GLfloat directionAng, GLfloat speed)
    {
        gXInit = x;
        gYInit = y;
        gZInit = z;
        gX = x;
        gY = y;
        gZ = z;
        gDirectionAng = directionAng;
        gSpeed = speed;
        gR = ((double)rand() / (RAND_MAX));
        gG = ((double)rand() / (RAND_MAX));
        gB = ((double)rand() / (RAND_MAX));

        GLfloat ViewingWidth = 500.0;
        GLfloat ViewingHeight = 500.0;

        head = Geometries::CreateSphere(radiusGunshot, 10);
        textureGunshot = Loader::LoadTextureRAW("img/sun1.bmp");
    };
    void draw();
    void move();
    bool valid();
    GLfloat getX()
    {
        return gX;
    };
    GLfloat getY()
    {
        return gY;
    };
    GLfloat getZ()
    {
        return gZ;
    };
    GLfloat getRadius();
};

#endif /* GUNSHOT_H */
