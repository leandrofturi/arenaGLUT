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

int walkStep = 0; // 5 steps of motion

void Puppet::drawLegs(GLfloat x, GLfloat y, GLfloat thetaLeg[2], GLfloat thetaThigh[2])
{
    gLegHeight = legHeight * cos(Geometries::toRad(thetaLeg[0]));
    gThighHeight = thighHeight * cos(Geometries::toRad(thetaThigh[0]));

    glPushMatrix();

    if (walkDirection < 0)
    {
        glRotatef(180.0, 0.0, 1.0, 0.0);
    }
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

    gArmElevation = armWidth / 2.0 * sin(Geometries::toRad(thetaArm));
    gArmTranslation = (armWidth / 2.0) - (armWidth / 2.0 * cos(Geometries::toRad(thetaArm)));

    glPushMatrix();

    glTranslatef(-gArmTranslation, gArmElevation, 0.0);
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
    glTranslatef(x, y, 0.0);

    drawLegs(x, y, thetaLeg, thetaThigh);
    glTranslatef(0.0, gLegHeight + gThighHeight, 0.0);
    drawBody(x, y);
    glTranslatef(0.0, bodyHeight / 2.0, 0.0);
    glPushMatrix();

    if (walkDirection < 0)
    {
        glRotatef(180.0, 0.0, 1.0, 0.0);
    }
    glTranslatef(armWidth / 2.0, 0.0, 0.0);

    drawArm(x, y, thetaArm);
    glPopMatrix();
    glTranslatef(0.0, bodyHeight / 2.0 + radiusHead, 0.0);
    drawHead(x, y);

    glPopMatrix();
}

void Puppet::takeStep(GLfloat x, GLfloat y, GLfloat dx)
{
    if (walkStep == 0)
    {
        thetaThigh[0] = 15.0;
        thetaThigh[1] = 15.0;
        thetaLeg[0] = 0.0;
        thetaLeg[1] = 0.0;
    }
    else if (walkStep == 1)
    {
        thetaThigh[0] = 30.0;
        thetaThigh[1] = 10.0;
        thetaLeg[0] = -40.0;
        thetaLeg[1] = 25.0;
    }
    else if (walkStep == 2)
    {
        thetaThigh[0] = 25.0;
        thetaThigh[1] = 15.0;
        thetaLeg[0] = -25.0;
        thetaLeg[1] = 35.0;
    }
    else if (walkStep == 3)
    {
        thetaThigh[0] = 25.0;
        thetaThigh[1] = 15.0;
        thetaLeg[0] = -5.0;
        thetaLeg[1] = 40.0;
    }
    else if (walkStep == 4)
    {
        thetaThigh[0] = 20.0;
        thetaThigh[1] = 15.0;
        thetaLeg[0] = -5.0;
        thetaLeg[1] = 15.0;
    }
    walkStep = (walkStep + 1) % 5;

    gX = gX + 50 * dx;
}

GLfloat totalHeight()
{
    return legHeight + bodyHeight + 2 * radiusHead;
}

void Puppet::takeFly(GLfloat x, GLfloat y, GLfloat dy)
{
    thetaThigh[0] = 15.0;
    thetaThigh[1] = 15.0;
    thetaLeg[0] = 0.0;
    thetaLeg[1] = 0.0;

    static int dir = 1;

    switch (flying)
    {
    case -1: // no
        break;
    case 0: // land
        dir = -1;
    case 1: // yes
        GLfloat h = dir * 10 * dy;
        if (gY + h > (3 * totalHeight()))
        {
            gY -= h;
            flying = 0;
        }
        else if (gY + h < 0)
        {
            flying = -1;
        }
        else
        {
            gY += h;
        }
        dir = 1;
        break;
    }
}

int sgn(GLfloat x)
{
    return (x > 0) - (x < 0);
}

void Puppet::rotateArm(GLfloat inc)
{
    gThetaArm = fabs(gThetaArm) > 45 ? 45 * sgn(gThetaArm) : gThetaArm + inc;
}

Gunshot *Puppet::shoot()
{
    GLfloat posShotX = gX,
            posShotY = gY + gLegHeight + gThighHeight + bodyHeight / 2.0 + armHeight / 2.0;
    GLfloat directionAng = gThetaArm;
    if (walkDirection < 0)
    {
        directionAng = sgn(gThetaArm) * 180 - directionAng;
    }
    Geometries::movePoint(posShotX, posShotY, directionAng, armWidth);

    Gunshot *shot = new Gunshot(posShotX, posShotY, directionAng);
    return shot;
}