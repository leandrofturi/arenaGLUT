#include "../include/puppet.h"
#include "../include/geometries.h"
#include <math.h>

// Dimensions
#define legHeight 30.0
#define legWidth 15.0
#define thighHeight 50.0
#define thighWidth 15.0
#define armHeight 10.0
#define armWidth 80.0
#define bodyHeight 100.0
#define bodyWidth 60.0
#define radiusHead 30.0
#define stepSize 20.0

int walkStepRight = 0; // 5 steps of motion
int walkStepLeft = 0;  // 5 steps of motion

void Puppet::drawLegs(GLfloat x, GLfloat y, GLfloat thetaLeg[2], GLfloat thetaThigh[2])
{
    gLegHeight = legHeight * cos(Geometries::toRad(thetaLeg[0]));
    gThighHeight = thighHeight * cos(Geometries::toRad(thetaThigh[0]));

    glPushMatrix();

    glRotatef(180.0, 0.0, 0.0, 1.0);
    glTranslatef(0.0, -gLegHeight - gThighHeight, 0.0);

    glPushMatrix();
    glRotatef(thetaThigh[0], 0.0, 0.0, 1.0);
    Geometries::drawRect(legHeight, legWidth, 1.0, 0.0, 0.0);

    glTranslatef(0.0, legHeight, 0.0);
    glRotatef(thetaLeg[0], 0.0, 0.0, 1.0);
    Geometries::drawRect(thighHeight, thighWidth, 1.0, 0.0, 0.0);

    glPopMatrix();
    glPushMatrix();

    glRotatef(-thetaThigh[1], 0.0, 0.0, 1.0);
    Geometries::drawRect(legHeight, legWidth, 1.0, 0.0, 0.0);

    glTranslatef(0.0, legHeight, 0.0);
    glRotatef(-thetaLeg[1], 0.0, 0.0, 1.0);
    Geometries::drawRect(thighHeight, thighWidth, 1.0, 0.0, 0.0);

    glPopMatrix();

    glPopMatrix();
}

void Puppet::drawArm(GLfloat x, GLfloat y, GLfloat thetaArm)
{

    gArmElevation = armWidth / 2 * sin(Geometries::toRad(thetaArm));
    gArmTranslation = (armWidth / 2) - (armWidth / 2 * cos(Geometries::toRad(thetaArm)));

    glPushMatrix();

    glTranslatef(-gArmTranslation * walkDirection, gArmElevation * walkDirection, 0.0);
    glRotatef(thetaArm, 0.0, 0.0, 1.0);
    Geometries::drawRect(armHeight, armWidth, 1.0, 1.0, 0.0);

    glPopMatrix();
}

void Puppet::drawBody(GLfloat x, GLfloat y)
{
    glPushMatrix();

    Geometries::drawRect(bodyHeight, bodyWidth, 0.0, 1.0, 0.0);

    glPopMatrix();
}

void Puppet::drawHead(GLfloat x, GLfloat y)
{
    glPushMatrix();

    Geometries::drawCircle(radiusHead, 0.0, 1.0, 0.0);

    glPopMatrix();
}

void Puppet::drawPuppet(GLfloat x, GLfloat y, GLfloat thetaLeg[2], GLfloat thetaThigh[2], GLfloat thetaArm)
{
    glPushMatrix();

    drawLegs(x, y, thetaLeg, thetaThigh);
    glTranslatef(0.0, Puppet::gLegHeight + Puppet::gThighHeight, 0.0);
    drawBody(x, y);
    glTranslatef(0.0, bodyHeight / 2, 0.0);
    glPushMatrix();
    if (walkDirection < 0)
    {
        glTranslatef(-bodyWidth / 2, 0.0, 0.0);
    }
    else
    {
        glTranslatef(bodyWidth / 2, 0.0, 0.0);
    }
    drawArm(x, y, thetaArm);
    glPopMatrix();
    glTranslatef(0.0, bodyHeight / 2 + radiusHead, 0.0);
    drawHead(x, y);

    glPopMatrix();
}

void Puppet::takeStepToRight(GLfloat x, GLfloat y, GLfloat dx)
{
    if (walkStepRight == 0)
    {
        thetaThigh[0] = 15.0;
        thetaThigh[1] = 15.0;
        thetaLeg[0] = 0.0;
        thetaLeg[1] = 0.0;
    }
    else if (walkStepRight == 1)
    {
        thetaThigh[0] = 30.0;
        thetaThigh[1] = 10.0;
        thetaLeg[0] = -40.0;
        thetaLeg[1] = 25.0;
    }
    else if (walkStepRight == 2)
    {
        thetaThigh[0] = 25.0;
        thetaThigh[1] = 15.0;
        thetaLeg[0] = -25.0;
        thetaLeg[1] = 35.0;
    }
    else if (walkStepRight == 3)
    {
        thetaThigh[0] = 25.0;
        thetaThigh[1] = 15.0;
        thetaLeg[0] = -5.0;
        thetaLeg[1] = 40.0;
    }
    else if (walkStepRight == 4)
    {
        thetaThigh[0] = 20.0;
        thetaThigh[1] = 15.0;
        thetaLeg[0] = -5.0;
        thetaLeg[1] = 15.0;
    }
    walkStepRight = (walkStepRight + 1) % 5;
    walkStepLeft = 0;
    walkDirection = 1;

    gX = gX + 10 * dx;
}

void Puppet::takeStepToLeft(GLfloat x, GLfloat y, GLfloat dx)
{
    if (walkStepLeft == 0)
    {
        thetaThigh[1] = 15.0;
        thetaThigh[0] = 15.0;
        thetaLeg[1] = 0.0;
        thetaLeg[0] = 0.0;
    }
    else if (walkStepLeft == 1)
    {
        thetaThigh[1] = 30.0;
        thetaThigh[0] = 10.0;
        thetaLeg[1] = -40.0;
        thetaLeg[0] = 25.0;
    }
    else if (walkStepLeft == 2)
    {
        thetaThigh[1] = 25.0;
        thetaThigh[0] = 15.0;
        thetaLeg[1] = -25.0;
        thetaLeg[0] = 35.0;
    }
    else if (walkStepLeft == 3)
    {
        thetaThigh[1] = 25.0;
        thetaThigh[0] = 15.0;
        thetaLeg[1] = -5.0;
        thetaLeg[0] = 40.0;
    }
    else if (walkStepLeft == 4)
    {
        thetaThigh[1] = 20.0;
        thetaThigh[0] = 15.0;
        thetaLeg[1] = -5.0;
        thetaLeg[0] = 15.0;
    }
    walkStepLeft = (walkStepLeft + 1) % 5;
    walkStepRight = 0;
    walkDirection = -1;

    gX = gX - 10 * dx;
}

int sgn(GLfloat x)
{
    return (x > 0) - (x < 0);
}

void Puppet::rotateArm(GLfloat inc)
{
    gThetaArm = fabs(gThetaArm) > 45 ? 45 * sgn(gThetaArm) : gThetaArm + inc * walkDirection;
}