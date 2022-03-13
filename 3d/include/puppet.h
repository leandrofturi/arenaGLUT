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
    GLfloat gThetaArm = 90.0;
    GLfloat gY0 = 0.0;
    GLfloat gLegHeight;
    GLfloat gThighHeight;
    GLfloat thetaLeg[2] = {0.0, 0.0};
    GLfloat thetaThigh[2] = {15.0, 15.0};
    GLfloat angPerna1;
    GLfloat angPerna2;
    GLfloat angPerna3;
    GLfloat angPerna4;

    OBJ *head;
    OBJ *body;
    GLuint texturePuppet;
    int walkDirection = 1; // -1: left, 1: right
    int direcao;

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
    void AnimaPerna(GLfloat dx);
    void takeStep(GLfloat x, GLfloat y, GLfloat dx);

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
};

#endif /* PUPPET_H */
