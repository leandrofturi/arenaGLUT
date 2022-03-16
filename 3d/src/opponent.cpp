#include "../include/opponent.h"
#include <math.h>
#include <cstdio>

#define legHeight 3.2
#define legWidth 1.2
#define legDepth 1.2
#define thighHeight 4.0
#define thighWidth 1.2
#define thighDepth 1.2
#define armHeight 0.96
#define armWidth 6.4
#define armDepth 0.96
#define bodyHeight 8.0
#define bodyWidth 4.8
#define bodyDepth 2.4
#define radiusHead 2.4
#define stepSize 1.6

void Opponent::init()
{
    head = Geometries::CreateSphere(radiusHead, 10);
    textureOpponent = Loader::LoadTextureRAW("img/earth.bmp");
}

GLfloat Opponent::getWidth()
{
    return bodyWidth;
}

GLfloat Opponent::getHeight()
{
    return legHeight + thighHeight + bodyHeight + radiusHead - thighDepth / 2.0;
}

GLfloat Opponent::getDepth()
{
    return bodyDepth;
}

void Opponent::draw()
{
    glPushMatrix();
    glTranslatef(gX, gY + getHeight(), gZ);

    drawHead();

    glPushAttrib(GL_ENABLE_BIT);
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);

    glPushMatrix();

    glTranslatef(0.0, -2.5 * radiusHead, 0.0);
    drawBody();
    drawArm();

    glTranslatef(0.0, -bodyHeight, 0.0);
    drawLegs();

    glPopMatrix();
    glPopAttrib();

    glPopMatrix();
}

int walkStepOp = 0; // 5 steps of motion

void Opponent::walk(double inc)
{
    if (inc < 0)
        walkDirection = 1;
    else
        walkDirection = -1;
    gX = gX + gSpeed * inc * cos((gCamXYAngle + 90.0) * 0.0174533);
    gZ = gZ + gSpeed * inc * sin((gCamXYAngle + 90.0) * 0.0174533);

    if (walkStepOp == 0)
    {
        thetaThigh[0] = 15.0;
        thetaThigh[1] = 15.0;
        thetaLeg[0] = 0.0;
        thetaLeg[1] = 0.0;
    }
    else if (walkStepOp == 1)
    {
        thetaThigh[0] = 35.0;
        thetaThigh[1] = 15.0;
        thetaLeg[0] = -45.0;
        thetaLeg[1] = 30.0;
    }
    else if (walkStepOp == 2)
    {
        thetaThigh[0] = 20.0;
        thetaThigh[1] = 10.0;
        thetaLeg[0] = -20.0;
        thetaLeg[1] = 30.0;
    }
    else if (walkStepOp == 3)
    {
        thetaThigh[0] = 30.0;
        thetaThigh[1] = 20.0;
        thetaLeg[0] = -10.0;
        thetaLeg[1] = 35.0;
    }
    else if (walkStepOp == 4)
    {
        thetaThigh[0] = 15.0;
        thetaThigh[1] = 10.0;
        thetaLeg[0] = 0.0;
        thetaLeg[1] = 10.0;
    }
    walkStepOp = (walkStepOp + 1) % 5;
}

void Opponent::jump(double inc)
{
    gY = gY + gSpeed * inc;
}

void Opponent::rotate(double inc)
{
    gCamXYAngle = (int)(gCamXYAngle + inc) % 360;
}

void Opponent::handleGravity()
{
    if (gY > gY0 && !isElevated())
    {
        gY = gY - gSpeed;
    }
}

int sgnOp(GLfloat x)
{
    return (x > 0) - (x < 0);
}

void Opponent::rotateArm(double inc)
{
    gArmAngle = fabs(gArmAngle) > 45 ? 45 * sgnOp(gArmAngle) : gArmAngle + inc;
}

void Opponent::drawLegs()
{
    gLegHeight = legHeight * cos(Geometries::toRad(thetaLeg[0]));
    gThighHeight = thighHeight * cos(Geometries::toRad(thetaThigh[0]));

    glPushMatrix();

    glRotatef(-90.0, 0.0, 1.0, 0.0);
    glRotatef(180.0, 1.0, 0.0, 0.0);
    glTranslatef(0.0, -gLegHeight, 0.0);

    glPushMatrix();
    if (walkDirection < 0)
        glRotatef(180, 0, 1, 0);

    glPushMatrix();
    glTranslatef(-legWidth / 2.0, 0.0, 0.0);

    glRotatef(thetaThigh[0], 0.0, 0.0, 1.0);
    Geometries::CreateSolidCube(legWidth, legHeight, legDepth, COLOR{0.0588, 0.2980, 0.5058});

    glTranslatef(0.0, legHeight, 0.0);
    glRotatef(thetaLeg[0], 0.0, 0.0, 1.0);
    if (walkStepOp != 0)
        glTranslatef(thighDepth / 2.0, 0.0, 0.0);
    Geometries::CreateSolidCube(thighWidth, thighHeight, thighDepth, COLOR{0.0588, 0.2980, 0.5058});

    glPopMatrix();
    glPushMatrix();
    glTranslatef(legWidth / 2.0, 0.0, 0.0);

    glRotatef(-thetaThigh[1], 0.0, 0.0, 1.0);
    Geometries::CreateSolidCube(legWidth, legHeight, legDepth, COLOR{0.0588, 0.2980, 0.5058});

    glTranslatef(0.0, legHeight, 0.0);
    glRotatef(-thetaLeg[1], 0.0, 0.0, 1.0);
    if (walkStepOp != 0)
        glTranslatef(thighDepth / 2.0, 0.0, 0.0);
    Geometries::CreateSolidCube(thighWidth, thighHeight, thighDepth, COLOR{0.0588, 0.2980, 0.5058});

    glPopMatrix();

    glPopMatrix();

    glPopMatrix();
}

void Opponent::drawArm()
{
    glPushMatrix();
    if (walkDirection < 0)
        glRotatef(-180, 1, 0, 0);

    glPushMatrix();

    glRotatef(gArmAngle * sgnOp(walkDirection), 1, 0, 0);

    glTranslatef(2.0 * bodyWidth / 3.0 - armDepth, 0.0, -armWidth / 2.0);
    glRotatef(90, 0, 1, 0);
    // glRotatef(-45, 0, 0, 1);
    Geometries::CreateSolidCube(armWidth, armHeight, armDepth, COLOR{0.0588, 0.2980, 0.5058});
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-2.0 * bodyWidth / 3.0 + armDepth, 0.0, -armWidth / 2.0);
    glRotatef(90, 0, 1, 0);
    // glRotatef(+45, 0, 0, 1);
    Geometries::CreateSolidCube(armWidth, armHeight, armDepth, COLOR{0.0588, 0.2980, 0.5058});
    glPopMatrix();
    glPopMatrix();
}

void Opponent::drawBody()
{
    Geometries::CreateSolidCube(bodyWidth, bodyHeight, bodyDepth, COLOR{0.0588, 0.2980, 0.5058});
}

void Opponent::drawHead()
{
    GLfloat materialEmission[] = {0.10, 0.10, 0.10, 1};
    GLfloat materialColorA[] = {0.2, 0.2, 0.2, 1};
    GLfloat materialColorD[] = {1.0, 1.0, 1.0, 1};
    GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1};
    GLfloat mat_shininess[] = {100.0};

    glPushMatrix();
    glRotatef(90, 1, 0, 0);

    glColor3f(1, 1, 1);

    glMaterialfv(GL_FRONT, GL_EMISSION, materialEmission);
    glMaterialfv(GL_FRONT, GL_AMBIENT, materialColorA);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, materialColorD);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, textureOpponent);
    glBegin(GL_TRIANGLE_STRIP);
    for (int i = 0; i < head->numVtx; i++)
    {
        glNormal3f(head->vtx[i].nX, head->vtx[i].nY, head->vtx[i].nZ);
        glTexCoord2f(head->vtx[i].U, head->vtx[i].V);
        glVertex3f(head->vtx[i].X, head->vtx[i].Y, head->vtx[i].Z);
    }
    glEnd();
    glPopMatrix();
}

Gunshot *Opponent::shoot()
{
    GLfloat posShotX = gZ,
            posShotY = gY + getHeight(),
            posShotZ = -gX;
    GLfloat angleXZ = gCamXYAngle;
    if (walkDirection > 0)
        angleXZ = gCamXYAngle + 180;
    else
        posShotX += 2.0 * armWidth;

    posShotY -= 2.0 * bodyHeight / 3.0 + armDepth;

    posShotX -= armWidth * cos(gArmAngle * 0.0174533);
    posShotY += armWidth * sin(gArmAngle * 0.0174533);

    Gunshot *shot = new Gunshot(posShotX, posShotY, posShotZ, angleXZ, gArmAngle, gSpeed * 3.0);
    return shot;
}

void Opponent::setLimits(GLfloat xLim[2], GLfloat zLim[2])
{
    gXLim[0] = xLim[0];
    gXLim[1] = xLim[1];
    gZLim[0] = zLim[0];
    gZLim[1] = zLim[1];
}

void Opponent::takeRandMoviment()
{
    if ((gZ + getWidth() >= gXLim[0]) || (gZ - getWidth() <= gXLim[1]) ||
        (gX + getWidth() <= gZLim[0]) || (gX - getWidth() >= gZLim[1]))
    {
        walkDirection *= -1;
    }
    walk(-walkDirection);
}