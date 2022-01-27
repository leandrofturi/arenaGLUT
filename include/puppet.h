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
    GLfloat gFlyYf = 0.0;

    GLfloat ArenaWidth = 500.0;
    GLfloat ArenaHeight = 500.0;

    int alive = 1;         // 0: no, 1: yes
    int walkDirection = 1; // -1: left, 1: right
    int stopped = 0;       // -1: left, 1: right
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
    void setInitial(GLfloat x, GLfloat y, GLfloat arenaWidth, GLfloat arenaHeight)
    {
        gX = x;
        gY = y;
        gY0 = y;
        gFlyYf = 0.0;
        ArenaWidth = arenaWidth;
        ArenaHeight = arenaHeight;
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
    GLfloat getSpeed()
    {
        return gSpeed;
    };
    void setY(GLfloat y)
    {
        gY = y;
    };
    GLfloat getHeight();
    GLfloat getWidth();
    void kill()
    {
        alive = 0;
    };
    bool walk(GLfloat dx)
    {
        if (stopped != walkDirection && gX + gSpeed * dx >= 0 && gX + gSpeed * dx <= ArenaWidth)
        {
            takeStep(gX, gY, dx);
            return true;
        }
        return false;
    };
    void stop(int dir)
    {
        stopped = dir;
    };
    void fly()
    {
        flying = 1;
        elevated = 0;
        stopped = 0;
        takeFly(gX, gY, gFlySpeed);
    };
    void shootDown()
    {
        flying = 0;
        elevated = 0;
    };
    void uncover()
    {
        gFlyYf = 0.0;
    }
    bool isFlying()
    {
        return flying;
    };
    void gravity()
    {
        if (!flying && !elevated && (fabs(gY - gY0) >= 1e-3))
        {
            takeFly(gX, gY, -gFlySpeed);
        }
    };
    bool isFalling()
    {
        return !flying && !elevated && (fabs(gY - gY0) >= 1e-3);
    };
    void elevate(GLfloat y)
    {
        gY = y;
        gFlyY0 = y;
        elevated = 1;
    };
    void cover(GLfloat y)
    {
        gFlyYf = y;
        shootDown();
    };
    void setDirection(int x)
    {
        walkDirection = (x > 0) - (x < 0);
    };
    int getDirection()
    {
        return walkDirection;
    };
};

#endif /* PUPPET_H */
