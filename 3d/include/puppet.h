#ifndef PUPPET_H
#define PUPPET_H
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include "geometries.h"
#include <cstdio>

class Puppet
{
    GLfloat gX = 0.0;
    GLfloat gY = 0.0;
    GLfloat gZ = 0.0;
    GLfloat gSpeed = 0.5;
    GLfloat gCamXYAngle = 0.0;
    GLfloat gThetaArm = 0.0;
    GLfloat gY0 = 0.0;
    GLfloat gXCollided = 0.0;
    GLfloat gYCollided = 0.0;
    GLfloat gZCollided = 0.0;

    GLfloat gLegHeight;
    GLfloat gThighHeight;
    GLfloat thetaLeg[2] = {0.0, 0.0};
    GLfloat thetaThigh[2] = {15.0, 15.0};

    OBJ *head;
    OBJ *body;
    GLuint texturePuppet;
    int walkDirection = 1; // -1: back, 1: front

public:
    void init();
    void draw();
    void walk(double inc);
    void jump(double inc);
    void rotate(double inc);
    void handleGravity();
    //void drawLegs(GLfloat x, GLfloat y, GLfloat thetaLeg[2], GLfloat thetaThigh[2]); // theta: angle referenced in the body
    void drawBody(GLfloat X, GLfloat Y);
    void drawHead(GLfloat x, GLfloat y);

    GLfloat getX()
    {
        return gX;
    }
    GLfloat getY()
    {
        return gY;
    }
    GLfloat getZ()
    {
        return gZ;
    }
    GLfloat getWidth()
    {
        return 2 * 2.4;
    }
    GLfloat getHeight()
    {
        return 2 * 2.4;
    }
    GLfloat getDepth()
    {
        return 2 * 2.4;
    }
    int getWalkDir()
    {
        return walkDirection;
    }
    void setX(GLfloat x)
    {
        gX = x;
    }
    void setY(GLfloat y)
    {
        gY = y;
    }
    void setY0(GLfloat y)
    {
        gY0 = y;
    }
    void setZ(GLfloat z)
    {
        gZ = z;
    }
    void elevate(bool c)
    {
        gYCollided = 0.0;
        if (c)
            gYCollided = gY;
    }
    bool isElevated()
    {
        return fabs(gYCollided) >= 1e-4;
    }
};

#endif /* PUPPET_H */
