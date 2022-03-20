#include "../include/gunshot.h"
#include "../include/geometries.h"
#include <stdlib.h>

void Gunshot::draw()
{
    if (gType == 0)
    {
        GLfloat materialEmission[] = {1.00, 1.00, 0.00, 1};
        GLfloat materialColor[] = {1.0, 1.0, 0.0, 1};
        GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1};
        GLfloat mat_shininess[] = {50.0};
        GLfloat color_r[] = {1.0, 0.0, 0.0, 1.0};
        GLfloat color_g[] = {0.0, 1.0, 0.0, 1.0};
        GLfloat color_b[] = {0.0, 0.0, 1.0, 1.0};

        glPushMatrix();
        glTranslatef(gX, gY, gZ);
        glColor3f(1, 0, 0);

        glMaterialfv(GL_FRONT, GL_EMISSION, materialEmission);
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glBindTexture(GL_TEXTURE_2D, textureGunshot);
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
    else
    {
        GLfloat materialEmission[] = {0.10, 0.10, 0.10, 1};
        GLfloat materialColorA[] = {0.2, 0.2, 0.2, 1};
        GLfloat materialColorD[] = {1.0, 1.0, 1.0, 1};
        GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1};
        GLfloat mat_shininess[] = {100.0};

        glPushMatrix();
        glTranslatef(gX, gY, gZ);
        glColor3f(1, 1, 1);

        glMaterialfv(GL_FRONT, GL_EMISSION, materialEmission);
        glMaterialfv(GL_FRONT, GL_AMBIENT, materialColorA);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, materialColorD);
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glBindTexture(GL_TEXTURE_2D, textureGunshot);
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
}

void Gunshot::move()
{
    gX = gX + gSpeed * cos(gAngleXZ * 0.0174533);
    gZ = gZ + gSpeed * sin(gAngleXZ * 0.0174533);

    gY = gY + gSpeed * sin(gAngleY * 0.0174533);
}

bool Gunshot::valid()
{
    return fmax(fabs(gX - gXInit), fabs(gZ - gZInit)) < maxDistance;
}
