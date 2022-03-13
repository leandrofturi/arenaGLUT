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

int walkStep = 0; 

// void Puppet::AnimaPerna(GLfloat dx){
//     // parar perna1 (max)
//     GLfloat maxAng1 = 45;
//     // parar perna1 
//     GLfloat maxAng2 = -45;
//     if(dx > 0){
//         direcao = 1;
//         //angBraco = -90;
//     }
//     if(dx < 0){
//         direcao = -1;
//         //angBraco = -270;
//     }
    
//     GLfloat x_1 = tan(angPerna1 * M_PI/180) * pernas;
//     GLfloat xd = x_1 + dx * perna1Status; 
//     GLfloat angNew = atan2(xd, pernas)* 180/M_PI;
//     //
//     if( abs(angNew) >= maxAng1){
//         perna1Status = perna1Status*(-1);
//         angPerna1 = angNew;
//     }
//     if(angNew < 0){
//         angPerna2 = -angNew;
//         angPerna4 = -angPerna1;
//     }else{
//         angPerna2 = angPerna1;
//         angPerna4 = angNew;
//     }
//     angPerna1 = angNew;
//     angPerna3 = -angNew;
    
// }

void Puppet::init()
{   
    COLOR color;
    color.R = 0.0;
    color.G = 1.0;
    color.B = 0.0;
    //
        
        head = Geometries::CreateSphere(radiusHead, 10);
    //glPopMatrix();
    // body = Geometries::CreateBody(bodyWidth,bodyHeight,(bodyWidth + bodyHeight)/2, color);
}

void Puppet::draw()
{
    GLfloat materialEmission[] = {1.00, 1.00, 0.00, 1};
    GLfloat materialColor[] = {1.0, 1.0, 0.0, 1};
    GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1};
    GLfloat mat_shininess[] = {50.0};
    GLfloat color_r[] = {1.0, 0.0, 0.0, 1.0};
    GLfloat color_g[] = {0.0, 1.0, 0.0, 1.0};
    GLfloat color_b[] = {0.0, 0.0, 1.0, 1.0};
    
    glTranslatef(gX, gY, gZ);
    glPushMatrix();
    glTranslatef(0.0, bodyHeight + 2 * legHeight, 0.0);
//glTranslatef(0.0, -bodyHeight / 2.0 - radiusHead, 0.0);
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
    // body

    glPushMatrix();
        glColor3fv(color_g);
        glTranslatef(0.0, bodyHeight, 0.0);
        COLOR color;
        color.R = 0.0;
        color.G = 1.0;
        color.B = 0.0;
        glScalef(bodyWidth, bodyHeight, (bodyWidth + bodyHeight)/2);
        glutSolidCube(1.0);
    glPopMatrix();
    // // arm
    glPushMatrix();
        glColor3fv(color_g);
        glRotatef(gThetaArm, 0.0, 1.0, 0.0);
        glScalef(armWidth, armHeight, (armHeight + armWidth)/4);
        glTranslatef(bodyWidth/6, bodyHeight, 0.0);
        glutSolidCube(1.0);
    glPopMatrix();
    // // legs
    
    glPushMatrix();
    glRotatef(180, 1.0, 0.0, 0.0); // rotacionei aqui para ficar padrao correto
    gLegHeight = 3.20;
    gThighHeight = 3.8637;
    glTranslatef(0.0, 0.0, 0.0);
    

    // Perna Direita
    glPushMatrix(); // esse push foi para fazer o translate das pernas
    // aqui fiz ele apontar para frente as pernas
    glRotatef(-90, 0.0, 1.0, 0.0);
    // aqui fiz ele estar um pouco a direita parecendo uma perna mesmo kk 
    glTranslatef(0.0, 0.0, -(bodyWidth)/4);
    glPushMatrix();
    glColor3fv(color_r);
    glTranslatef(-legWidth / 2.0, 0.0, 0.0);
    glRotatef(thetaThigh[0], 0.0, 0.0, 1.0);
    glScalef(legWidth, legHeight, (legHeight + legWidth)/4);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glColor3fv(color_r);
    glTranslatef(0.0, -legHeight, 0.0);
    glRotatef(thetaLeg[0], 0.0, 0.0, 1.0);
    glScalef(legWidth, legHeight, (legHeight + legWidth)/4);
    glutSolidCube(1.0);
    glPopMatrix();

    glPopMatrix();
    // Perna da direita feita acima 

    // Perna Esquerda 
    glPushMatrix();
    // aqui fiz ele apontar para frente as pernas
    glRotatef(90, 0.0, 1.0, 0.0);
    // aqui fiz ele estar um pouco a direita parecendo uma perna mesmo kk 
    glTranslatef(-1.0, 0.0, -(bodyWidth)/4);

    glPushMatrix();
    glTranslatef(0.0, -legHeight, 0.0);
    glColor3fv(color_r);
    glRotatef(-thetaLeg[1], 0.0, 0.0, 1.0);
    glScalef(legWidth, legHeight, (legHeight + legWidth)/4);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glColor3fv(color_r);
    glTranslatef(legWidth / 2.0, 0.0, 0.0);
    glRotatef(-thetaThigh[1], 0.0, 0.0, 1.0);
    glScalef(legWidth, legHeight, (legHeight + legWidth)/4);
    glutSolidCube(1.0);
    glPopMatrix();


    
    
    glPopMatrix();

    glPopMatrix();
}

void Puppet::drawBody(GLfloat x, GLfloat y){
    glPushMatrix();
        glTranslatef(0,5,0);
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


void Puppet::walk(double inc)
{
    gX = gX + gSpeed * inc * cos((gCamXYAngle + 90.0) * 0.0174533);
    gZ = gZ + gSpeed * inc * sin((gCamXYAngle + 90.0) * 0.0174533);
    Puppet::takeStep(gX, gY, inc);
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