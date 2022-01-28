#include "../include/puppet.h"
#include "../include/geometries.h"
#include "../include/collision.h"
#include <math.h>
#include <cstdio>

#define legHeight 3.2
#define legWidth 1.2
#define thighHeight 4.0
#define thighWidth 1.2
#define armHeight 0.96
#define armWidth 6.4
#define bodyHeight 8.0
#define bodyWidth 4.8
#define radiusHead 2.4
#define stepSize 1.6

int walkStep = 0; // 5 steps of motion

void Puppet::drawLegs(GLfloat x, GLfloat y, GLfloat thetaLeg[2], GLfloat thetaThigh[2])
{
    gLegHeight = legHeight * cos(Geometries::toRad(thetaLeg[0]));
    gThighHeight = thighHeight * cos(Geometries::toRad(thetaThigh[0]));

    glPushMatrix();
    glTranslatef(0.0, -gLegHeight - gThighHeight, 0.0);

    if (walkDirection > 0)
    {
        glTranslatef(legWidth / 2.0, 0.0, 0.0);
        glRotatef(180.0, 0.0, 1.0, 0.0);
    }
    else
    {
        glTranslatef(-legWidth / 2.0, 0.0, 0.0);
    }

    glPushMatrix();
    glTranslatef(-legWidth / 2.0, 0.0, 0.0);

    glRotatef(thetaThigh[0], 0.0, 0.0, 1.0);
    if (alive)
    {
        Geometries::drawRect(legHeight, legWidth, 1.0, 0.0, 0.0);
    }
    else
    {
        Geometries::drawRect(legHeight, legWidth, 1.0, 1.0, 1.0);
    }

    glTranslatef(0.0, legHeight, 0.0);
    glRotatef(thetaLeg[0], 0.0, 0.0, 1.0);
    if (alive)
    {
        Geometries::drawRect(thighHeight, thighWidth, 1.0, 0.0, 0.0);
    }
    else
    {
        Geometries::drawRect(thighHeight, thighWidth, 1.0, 1.0, 1.0);
    }

    glPopMatrix();
    glPushMatrix();
    glTranslatef(legWidth / 2.0, 0.0, 0.0);

    glRotatef(-thetaThigh[1], 0.0, 0.0, 1.0);
    if (alive)
    {
        Geometries::drawRect(legHeight, legWidth, 1.0, 0.0, 0.0);
    }
    else
    {
        Geometries::drawRect(legHeight, legWidth, 1.0, 1.0, 1.0);
    }

    glTranslatef(0.0, legHeight, 0.0);
    glRotatef(-thetaLeg[1], 0.0, 0.0, 1.0);
    if (alive)
    {
        Geometries::drawRect(thighHeight, thighWidth, 1.0, 0.0, 0.0);
    }
    else
    {
        Geometries::drawRect(thighHeight, thighWidth, 1.0, 1.0, 1.0);
    }

    glPopMatrix();

    glPopMatrix();
}

void Puppet::drawArm(GLfloat x, GLfloat y, GLfloat thetaArm)
{
    glPushMatrix();

    glRotatef(thetaArm, 0.0, 0.0, 1.0);
    if (alive)
    {
        Geometries::drawRect(armHeight, armWidth, 1.0, 1.0, 0.0);
    }
    else
    {
        Geometries::drawRect(armHeight, armWidth, 1.0, 1.0, 1.0);
    }

    glPopMatrix();
}

void Puppet::drawBody(GLfloat x, GLfloat y)
{
    glPushMatrix();
    glTranslatef(-bodyWidth / 2.0, 0.0, 0.0);

    if (alive)
    {
        Geometries::drawRect(bodyHeight, bodyWidth, 0.0, 1.0, 0.0);
    }
    else
    {
        Geometries::drawRect(bodyHeight, bodyWidth, 1.0, 1.0, 1.0);
    }

    glPopMatrix();
}

void Puppet::drawHead(GLfloat x, GLfloat y)
{
    glPushMatrix();

    if (alive)
    {
        Geometries::drawCircle(radiusHead, 0.0, 1.0, 0.0);
    }
    else
    {
        Geometries::drawCircle(radiusHead, 1.0, 1.0, 1.0);
    }

    glPopMatrix();
}

void Puppet::drawPuppet(GLfloat x, GLfloat y, GLfloat thetaLeg[2], GLfloat thetaThigh[2], GLfloat thetaArm)
{
    glPushMatrix();
    glTranslatef(x, y, 0.0);

    drawLegs(x, y, thetaLeg, thetaThigh);
    // Geometries::drawCircle(1.0, 1.0, 1.0, 1.0);
    glTranslatef(0.0, -gLegHeight - gThighHeight - 0.9 * bodyHeight, 0.0);
    drawBody(x, y);
    glTranslatef(0.0, bodyHeight / 2.0, 0.0);
    glPushMatrix();

    if (walkDirection < 0)
    {
        glRotatef(180.0, 0.0, 1.0, 0.0);
    }

    drawArm(x, y, thetaArm);
    glPopMatrix();
    glTranslatef(0.0, -bodyHeight / 2.0 - radiusHead, 0.0);
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

    gX = gX + gSpeed * dx;
}

GLfloat Puppet::getHeight()
{
    return legHeight + thighHeight + bodyHeight + 2.0 * radiusHead;
}

GLfloat Puppet::getWidth()
{
    return bodyWidth;
}

void Puppet::takeFly(GLfloat x, GLfloat y, GLfloat dy)
{
    thetaThigh[0] = 15.0;
    thetaThigh[1] = 15.0;
    thetaLeg[0] = 0.0;
    thetaLeg[1] = 0.0;

    GLfloat h = gFlySpeed * dy;
    GLfloat hP = getHeight();

    if (gY - h - hP <= gFlyYf) // top limit
    {
        flying = 0;
        return;
    }
    if (gY - h > gY0) // bottom limit
    {
        gY = gY0;
        flying = 0;
        return;
    }
    gY -= h;
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
            posShotY = gY - gLegHeight - gThighHeight - bodyHeight / 2.0 + 3.0 * armHeight / 2.0;
    GLfloat directionAng = gThetaArm;
    if (walkDirection < 0)
    {
        directionAng = sgn(gThetaArm) * 180 - directionAng;
    }
    Geometries::movePoint(posShotX, posShotY, directionAng, armWidth);

    Gunshot *shot = new Gunshot(posShotX, posShotY, directionAng, gSpeed / 20.0);
    return shot;
}
