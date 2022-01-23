#ifndef PUPPET_H
#define PUPPET_H
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include "gunshot.h"
#include <cstdio>

class Puppet
{
    GLfloat gX;
    GLfloat gY;
    GLfloat gY0 = 0.0;
    GLfloat thetaLeg[2] = {0.0, 0.0};
    GLfloat thetaThigh[2] = {15.0, 15.0};
    GLfloat gThetaArm = 0.0;
    GLfloat gLegHeight;
    GLfloat gThighHeight;
    GLfloat gSpeed = 50.0;
    GLfloat gFlySpeed = 1.0;
    GLfloat gFlyY0 = 0.0;

    int walkDirection = 1; // -1: left, 1: right
    int flying = 0;        // 0: no, 1: yes
    int elevated = 0;      // 0: no, 1: yes

private:
    void drawLegs(GLfloat x, GLfloat y, GLfloat thetaLeg[2], GLfloat thetaThigh[2]); // theta: angle referenced in the body
    void drawArm(GLfloat x, GLfloat y, GLfloat thetaArm);                            // theta: angle that varies 90'
    void drawBody(GLfloat x, GLfloat y);
    void drawHead(GLfloat x, GLfloat y);
    void drawPuppet(GLfloat x, GLfloat y, GLfloat thetaLeg[2], GLfloat thetaThigh[2], GLfloat thetaArm);
    void takeStep(GLfloat x, GLfloat y, GLfloat dx);
    void takeFly(GLfloat x, GLfloat y, GLfloat dy);

public:
    Puppet(){};
    void draw()
    {
        drawPuppet(gX, gY, thetaLeg, thetaThigh, gThetaArm);
    };
    void setInitial(GLfloat x, GLfloat y)
    {
        gX = x;
        gY = y;
        gY0 = y;
    };
    void rotateArm(GLfloat inc);
    Gunshot *shoot();
    GLfloat getX()
    {
        return gX;
    };
    GLfloat getY()
    {
        return gY;
    };
    GLfloat getHeight();
    GLfloat getWidth();
    void walk(GLfloat dx)
    {
        takeStep(gX, gY, dx);
    };
    void fly()
    {
        flying = 1;
        elevated = 0;
        takeFly(gX, gY, gFlySpeed);
    };
    void shootDown()
    {
        flying = 0;
        elevated = 0;
    };
    bool isFlying()
    {
        return flying;
    };
    void gravity()
    {
        if (!flying && !elevated)
        {
            if (fabs(gY - gY0) >= 1e-3)
            {
                takeFly(gX, gY, -gFlySpeed);
            }
        }
    };
    void elevate(GLfloat y)
    {
        gY = y;
        gFlyY0 = y;
        elevated = 1;
    };
    void setDirection(int x)
    {
        walkDirection = (x > 0) - (x < 0);
    };
};

#endif /* PUPPET_H */
