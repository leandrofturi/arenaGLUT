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
    //glRotatef(-180, 0.0, 0.0, 1.0);
    // aqui fiz ele estar um pouco a direita parecendo uma perna mesmo kk 
    glTranslatef(-1.0, 0.0, -(bodyWidth)/4);

    glPushMatrix();
    glTranslatef(0.0, -legHeight, 0.0);
    glColor3fv(color_r);
    glRotatef(-thetaLeg[1], 0.0, 0.0, 1.0);
    glScalef(legWidth, legHeight, (legHeight + legWidth)/4);
    glutSolidCube(1.0);
    glPopMatrix();

    // glPushMatrix();
    // glColor3fv(color_r);
    // glTranslatef(legWidth / 2.0, 0.0, 0.0);
    // glRotatef(-thetaThigh[1], 0.0, 0.0, 1.0);
    // glScalef(legWidth, legHeight, (legHeight + legWidth)/4);
    // glutSolidCube(1.0);
    // glPopMatrix();


    
    
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