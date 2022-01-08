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
    GLfloat gArmElevation;
    GLfloat gArmTranslation;

    int walkDirection = 1; // -1: left, 1: right

private:
    void drawLegs(GLfloat x, GLfloat y, GLfloat thetaLeg[2], GLfloat thetaThigh[2]); // theta: angle referenced in the body
    void drawArm(GLfloat x, GLfloat y, GLfloat thetaArm);                            // theta: angle that varies 90'
    void drawBody(GLfloat x, GLfloat y);
    void drawHead(GLfloat x, GLfloat y);
    void drawPuppet(GLfloat x, GLfloat y, GLfloat thetaLeg[2], GLfloat thetaThigh[2], GLfloat thetaArm);
    void takeStepToRight(GLfloat x, GLfloat y, GLfloat dx);
    void takeStepToLeft(GLfloat x, GLfloat y, GLfloat dx);

public:
    Puppet()
    {
        gX = 0.0;
        gY = -200.0;
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
    void walkToRight(GLfloat dx)
    {
        takeStepToRight(gX, gY, dx);
    };
    void walkToLeft(GLfloat dx)
    {
        takeStepToLeft(gX, gY, dx);
    };
    void setDirection(int x)
    {
        walkDirection = (x > 0) - (x < 0);
    };
};

#endif /* PUPPET_H */
