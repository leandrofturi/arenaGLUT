#ifndef GUNSHOT_H
#define GUNSHOT_H
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include "geometries.h"
#include "imageloader.h"

#define maxDistance 500

class Gunshot
{
    GLfloat radiusGunshot = 1;
    GLfloat gXInit;
    GLfloat gYInit;
    GLfloat gZInit;
    GLfloat gX;
    GLfloat gY;
    GLfloat gZ;
    GLfloat gAngleXZ;
    GLfloat gAngleY;
    GLfloat gSpeed;
    GLfloat gR;
    GLfloat gG;
    GLfloat gB;
    GLuint textureGunshot;

    OBJ *head;

public:
    Gunshot(GLfloat x, GLfloat y, GLfloat z, GLfloat angleXZ, GLfloat angleY, GLfloat speed)
    {
        gXInit = x;
        gYInit = y;
        gZInit = z;
        gX = x;
        gY = y;
        gZ = z;
        gAngleXZ = angleXZ;
        gAngleY = angleY;
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
    GLfloat getWidth()
    {
        return radiusGunshot;
    };
    GLfloat getHeight()
    {
        return radiusGunshot;
    };
    GLfloat getDepth()
    {
        return radiusGunshot;
    };
    void bump()
    {
        gX = gY = gZ = maxDistance;
    }
};

#endif /* GUNSHOT_H */
