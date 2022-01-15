#ifndef PUPPET_H
#define PUPPET_H
#include <GL/gl.h>
#include <GL/glu.h>
#include "gunshot.h"

class Puppet
{
    GLfloat gX;
    GLfloat gY;
    GLfloat thetaLeg[2] = {0.0, 0.0};
    GLfloat thetaThigh[2] = {15.0, 15.0};
    GLfloat gThetaArm = 0.0;
    GLfloat gLegHeight;
    GLfloat gThighHeight;
    GLfloat gFlySpeed = 1.0;

    int walkDirection = 1; // -1: left, 1: right
    int flying = -1;       // -1: no, 0: landing, 1: yes

private:
    void drawLegs(GLfloat x, GLfloat y, GLfloat thetaLeg[2], GLfloat thetaThigh[2]); // theta: angle referenced in the body
    void drawArm(GLfloat x, GLfloat y, GLfloat thetaArm);                            // theta: angle that varies 90'
    void drawBody(GLfloat x, GLfloat y);
    void drawHead(GLfloat x, GLfloat y);
    void drawPuppet(GLfloat x, GLfloat y, GLfloat thetaLeg[2], GLfloat thetaThigh[2], GLfloat thetaArm);
    void takeStep(GLfloat x, GLfloat y, GLfloat dx);
    void takeFly(GLfloat x, GLfloat y, GLfloat dy);

public:
    Puppet()
    {
        gX = 50.0;
        gY = 0.0;
    };
    void draw()
    {
        drawPuppet(gX, gY, thetaLeg, thetaThigh, gThetaArm);
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
    void walk(GLfloat dx)
    {
        takeStep(gX, gY, dx);
    };
    void fly()
    {
        takeFly(gX, gY, gFlySpeed);
    };
    void liftOff()
    {
        flying = 1;
    };
    void land()
    {
        flying = 0;
    };
    void setDirection(int x)
    {
        walkDirection = (x > 0) - (x < 0);
    };
    int isInTheAir()
    {
        return flying >= 0;
    };
    int landing()
    {
        return flying == 0;
    };
};

#endif /* PUPPET_H */
