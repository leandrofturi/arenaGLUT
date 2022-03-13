#include "../include/puppet.h"
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

void Puppet::init()
{
    head = Geometries::CreateSphere(radiusHead, 10);
    texturePuppet = Loader::LoadTextureRAW("img/sun1.bmp");

    // glShadeModel(GL_SMOOTH);
    // glEnable(GL_LIGHTING);
    // glEnable(GL_LIGHT0);
    // glEnable(GL_DEPTH_TEST);

    //Carrega as meshes dos arquivos
    movIdle = meshPuppet.loadMeshAnim("blender/idle/ninja_idle_######.obj", 40);
    movPunch = meshPuppet.loadMeshAnim("blender/punch/ninja_punching_######.obj", 35);
    movKick = meshPuppet.loadMeshAnim("blender/kick/ninja_kick_######.obj", 35);
    movDance = meshPuppet.loadMeshAnim("blender/dance/ninja_dance_######.obj", 90);
    meshPuppet.loadTexture("img/stars1.bmp");

    meshPuppet.drawInit(movIdle);
}

GLfloat Puppet::getWidth()
{
    return bodyWidth;
}

GLfloat Puppet::getHeight()
{
    return legHeight + thighHeight + bodyHeight + radiusHead - thighDepth / 2.0;
}

GLfloat Puppet::getDepth()
{
    return bodyDepth;
}

void Puppet::draw()
{
    glPushMatrix();
    glTranslatef(gX, gY + getHeight(), gZ);

    if (!animated)
    {
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
    }
    else
    {
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();

        glPushAttrib(GL_ENABLE_BIT);

        //Translada para o centro do lutador para facilitar a rotacao da camera
        glTranslatef(0, -getHeight(), 0);

        glScalef(0.25, 0.25, 0.25);
        if (walkDirection > 0)
            glRotatef(180.0, 0.0, 1.0, 0.0);

        //Escolhe entre iniciar o desenho do chute ou soco
        if (kicking && !acting)
        {
            meshPuppet.drawInit(movKick);
            acting = 1;
        }
        else if (punching && !acting)
        {
            meshPuppet.drawInit(movPunch);
            acting = 1;
        }
        else if (dancing && !acting)
        {
            meshPuppet.drawInit(movDance);
            acting = 1;
        }

        //Desenha as proximas frames ateh acabar
        int rtn = meshPuppet.drawNext();
        //Reinicia com o movimento de parado esperando a luta
        if (rtn)
        {
            meshPuppet.drawInit(movIdle);
            acting = 0;
            punching = 0;
            kicking = 0;
            dancing = 0;
        }
        glPopAttrib();
        glPopMatrix();
    }

    glPopMatrix();
}

int walkStep = 0; // 5 steps of motion

void Puppet::walk(double inc)
{
    if (inc < 0)
        walkDirection = 1;
    else
        walkDirection = -1;
    gX = gX + gSpeed * inc * cos((gCamXYAngle + 90.0) * 0.0174533);
    gZ = gZ + gSpeed * inc * sin((gCamXYAngle + 90.0) * 0.0174533);

    if (walkStep == 0)
    {
        thetaThigh[0] = 15.0;
        thetaThigh[1] = 15.0;
        thetaLeg[0] = 0.0;
        thetaLeg[1] = 0.0;
    }
    else if (walkStep == 1)
    {
        thetaThigh[0] = 35.0;
        thetaThigh[1] = 15.0;
        thetaLeg[0] = -45.0;
        thetaLeg[1] = 30.0;
    }
    else if (walkStep == 2)
    {
        thetaThigh[0] = 20.0;
        thetaThigh[1] = 10.0;
        thetaLeg[0] = -20.0;
        thetaLeg[1] = 30.0;
    }
    else if (walkStep == 3)
    {
        thetaThigh[0] = 30.0;
        thetaThigh[1] = 20.0;
        thetaLeg[0] = -10.0;
        thetaLeg[1] = 35.0;
    }
    else if (walkStep == 4)
    {
        thetaThigh[0] = 15.0;
        thetaThigh[1] = 10.0;
        thetaLeg[0] = 0.0;
        thetaLeg[1] = 10.0;
    }
    walkStep = (walkStep + 1) % 5;
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
    if (gY > gY0 && !isElevated())
    {
        gY = gY - gSpeed;
    }
}

int sgn(GLfloat x)
{
    return (x > 0) - (x < 0);
}

void Puppet::rotateArm(double inc)
{
    gArmAngle = fabs(gArmAngle) > 45 ? 45 * sgn(gArmAngle) : gArmAngle + inc;
}

void Puppet::drawLegs()
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
    Geometries::CreateSolidCube(legWidth, legHeight, legDepth, COLOR{0.15, 0.15, 0.15});

    glTranslatef(0.0, legHeight, 0.0);
    glRotatef(thetaLeg[0], 0.0, 0.0, 1.0);
    if (walkStep != 0)
        glTranslatef(thighDepth / 2.0, 0.0, 0.0);
    Geometries::CreateSolidCube(thighWidth, thighHeight, thighDepth, COLOR{0.15, 0.15, 0.15});

    glPopMatrix();
    glPushMatrix();
    glTranslatef(legWidth / 2.0, 0.0, 0.0);

    glRotatef(-thetaThigh[1], 0.0, 0.0, 1.0);
    Geometries::CreateSolidCube(legWidth, legHeight, legDepth, COLOR{0.15, 0.15, 0.15});

    glTranslatef(0.0, legHeight, 0.0);
    glRotatef(-thetaLeg[1], 0.0, 0.0, 1.0);
    if (walkStep != 0)
        glTranslatef(thighDepth / 2.0, 0.0, 0.0);
    Geometries::CreateSolidCube(thighWidth, thighHeight, thighDepth, COLOR{0.15, 0.15, 0.15});

    glPopMatrix();

    glPopMatrix();

    glPopMatrix();
}

void Puppet::drawArm()
{
    glPushMatrix();
    if (walkDirection < 0)
        glRotatef(-180, 1, 0, 0);

    glPushMatrix();

    glRotatef(gArmAngle * sgn(walkDirection), 1, 0, 0);

    glTranslatef(2.0 * bodyWidth / 3.0 - armDepth, 0.0, -armWidth / 2.0);
    glRotatef(90, 0, 1, 0);
    // glRotatef(-45, 0, 0, 1);
    Geometries::CreateSolidCube(armWidth, armHeight, armDepth, COLOR{0.15, 0.15, 0.15});
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-2.0 * bodyWidth / 3.0 + armDepth, 0.0, -armWidth / 2.0);
    glRotatef(90, 0, 1, 0);
    // glRotatef(+45, 0, 0, 1);
    Geometries::CreateSolidCube(armWidth, armHeight, armDepth, COLOR{0.15, 0.15, 0.15});
    glPopMatrix();
    glPopMatrix();
}

void Puppet::drawBody()
{
    Geometries::CreateSolidCube(bodyWidth, bodyHeight, bodyDepth, COLOR{0.15, 0.15, 0.15});
}

void Puppet::drawHead()
{
    GLfloat materialEmission[] = {1.00, 1.00, 0.00, 1};
    GLfloat materialColor[] = {1.0, 1.0, 0.0, 1};
    GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1};
    GLfloat mat_shininess[] = {50.0};
    GLfloat color_r[] = {1.0, 0.0, 0.0, 1.0};
    GLfloat color_g[] = {0.0, 1.0, 0.0, 1.0};
    GLfloat color_b[] = {0.0, 0.0, 1.0, 1.0};

    glPushMatrix();
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
    glPopMatrix();
}

Gunshot *Puppet::shoot()
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