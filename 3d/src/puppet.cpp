#include "../include/puppet.h"
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

void Puppet::init()
{   
    COLOR color;
    color.R = 0.0;
    color.G = 1.0;
    color.B = 0.0;
    head = Geometries::CreateSphere(radiusHead, 10);
    // body = Geometries::CreateBody(bodyWidth,bodyHeight,(bodyWidth + bodyHeight)/2, color);
}

void Puppet::draw()
{
    GLfloat materialEmission[] = {1.00, 1.00, 0.00, 1};
    GLfloat materialColor[] = {1.0, 1.0, 0.0, 1};
    GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1};
    GLfloat mat_shininess[] = {50.0};
    
    glTranslatef(gX, gY, gZ);

    glColor3f(1, 0, 0);

    glMaterialfv(GL_FRONT, GL_EMISSION, materialEmission);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, texturePuppet);
    glBegin(GL_TRIANGLE_STRIP);
    for (int i = 0; i < head->numVtx; i++)
    {
        glNormal3f(head->vtx[i].nX, head->vtx[i].nY, head->vtx[i].nZ);
        glTexCoord2f(head->vtx[i].U, head->vtx[i].V);
        glVertex3f(head->vtx[i].X, head->vtx[i].Y, head->vtx[i].Z);
    }
    glEnd();
    // body
    glPushMatrix();
        glTranslatef(0.0, - 0.9 * bodyHeight, 0.0);
        COLOR color;
        color.R = 0.0;
        color.G = 1.0;
        color.B = 0.0;
        Geometries::CreateSolidCube(bodyWidth,bodyHeight,(bodyWidth + bodyHeight)/2, color);
    glPopMatrix();
    // head
    glPushMatrix();
        glTranslatef(0.0, -bodyHeight / 2.0 - radiusHead, 0.0);
        COLOR colorHead;
        color.R = 0.0;
        color.G = 1.0;
        color.B = 0.0;
        Geometries::CreateSolidSphere(radiusHead,colorHead);
    glPopMatrix();
    // arm
    glPushMatrix();
        glRotatef(gThetaArm, 0.0, 0.0, 1.0);
        glTranslatef(-bodyWidth / 2.0, 0.0, 0.0);
        COLOR colorArm;
        color.R = 0.0;
        color.G = 1.0;
        color.B = 1.0;
        Geometries::CreateSolidCube(armWidth, armHeight, (armHeight + armHeight)/2,colorArm);
    glPopMatrix();
    // legs
    
    glPushMatrix();
         gLegHeight = 3.20;
     gThighHeight = 3.863703;
        glTranslatef(0.0, -gLegHeight - gThighHeight, 0.0);
        COLOR colorLeg;
        color.R = 1.0;
        color.G = 0.0;
        color.B = 0.0;
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
        Geometries::CreateSolidCube(legWidth, legHeight, (legHeight + legWidth)/2, colorLeg);
        glTranslatef(0.0, legHeight, 0.0);
    glRotatef(thetaLeg[0], 0.0, 0.0, 1.0);
    Geometries::CreateSolidCube(legWidth, legHeight, (legHeight + legWidth)/2, colorLeg);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(legWidth / 2.0, 0.0, 0.0);

    glRotatef(-thetaThigh[1], 0.0, 0.0, 1.0);
    Geometries::CreateSolidCube(legWidth, legHeight, (legHeight + legWidth)/2, colorLeg);
    glTranslatef(0.0, legHeight, 0.0);
    glRotatef(-thetaLeg[1], 0.0, 0.0, 1.0);
    Geometries::CreateSolidCube(legWidth, legHeight, (legHeight + legWidth)/2, colorLeg);
    glPopMatrix();

    glPopMatrix();
}

void Puppet::drawBody(GLfloat x, GLfloat y){
    glPushMatrix();
        glTranslatef(0,5,0);
    glPopMatrix();
}

// void Puppet::drawHead(){

// }

void Puppet::walk(double inc)
{
    gX = gX + gSpeed * inc * cos((gCamXYAngle + 90.0) * 0.0174533);
    gZ = gZ + gSpeed * inc * sin((gCamXYAngle + 90.0) * 0.0174533);
}

void Puppet::jump(double inc)
{
    gY = gY + gSpeed * inc;
}

void Puppet::rotate(double inc)
{
    gCamXYAngle = (int)(gCamXYAngle + inc) % 360;
}

void Puppet::handleGravity()
{
    if (gY > gY0)
    {
        gY = gY - gSpeed;
    }
}