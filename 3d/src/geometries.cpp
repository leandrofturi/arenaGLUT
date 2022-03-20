#include "../include/geometries.h"
#include <math.h>

OBJ *Geometries::CreateSphere(double R, double space)
{
    OBJ *obj = new OBJ;

    obj->numVtx = (180 / space) * (2 + 360 / (2 * space)) * 4;
    obj->vtx = new VERTICES[obj->numVtx];
    obj->radius = R;

    int n;
    double vR, lVR;
    double hR, lHR;
    double norm;
    n = 0;
    for (vR = 0; vR <= 180 - space; vR += space)
    {
        for (hR = 0; hR <= 360 + 2 * space; hR += 2 * space)
        {
            lVR = vR;
            lHR = hR;
            obj->vtx[n].X = R *
                            sin(lHR / 180 * M_PI) *
                            sin(lVR / 180 * M_PI);
            obj->vtx[n].Y = R *
                            cos(lHR / 180 * M_PI) *
                            sin(lVR / 180 * M_PI);
            obj->vtx[n].Z = R *
                            cos(lVR / 180 * M_PI);
            obj->vtx[n].V = lVR / 180;
            obj->vtx[n].U = lHR / 360;
            norm = sqrt(
                obj->vtx[n].X * obj->vtx[n].X +
                obj->vtx[n].Y * obj->vtx[n].Y +
                obj->vtx[n].Z * obj->vtx[n].Z);
            obj->vtx[n].nX = obj->vtx[n].X / norm;
            obj->vtx[n].nY = obj->vtx[n].Y / norm;
            obj->vtx[n].nZ = obj->vtx[n].Z / norm;
            n++;

            lVR = vR + space;
            lHR = hR;
            obj->vtx[n].X = R * sin(lHR / 180 * M_PI) * sin(lVR / 180 * M_PI);
            obj->vtx[n].Y = R * cos(lHR / 180 * M_PI) * sin(lVR / 180 * M_PI);
            obj->vtx[n].Z = R * cos(lVR / 180 * M_PI);
            obj->vtx[n].V = lVR / 180;
            obj->vtx[n].U = lHR / 360;
            norm = sqrt(obj->vtx[n].X * obj->vtx[n].X + obj->vtx[n].Y * obj->vtx[n].Y + obj->vtx[n].Z * obj->vtx[n].Z);
            obj->vtx[n].nX = obj->vtx[n].X / norm;
            obj->vtx[n].nY = obj->vtx[n].Y / norm;
            obj->vtx[n].nZ = obj->vtx[n].Z / norm;
            n++;

            lVR = vR;
            lHR = hR + space;
            obj->vtx[n].X = R * sin(lHR / 180 * M_PI) * sin(lVR / 180 * M_PI);
            obj->vtx[n].Y = R * cos(lHR / 180 * M_PI) * sin(lVR / 180 * M_PI);
            obj->vtx[n].Z = R * cos(lVR / 180 * M_PI);
            obj->vtx[n].V = lVR / 180;
            obj->vtx[n].U = lHR / 360;
            norm = sqrt(obj->vtx[n].X * obj->vtx[n].X + obj->vtx[n].Y * obj->vtx[n].Y + obj->vtx[n].Z * obj->vtx[n].Z);
            obj->vtx[n].nX = obj->vtx[n].X / norm;
            obj->vtx[n].nY = obj->vtx[n].Y / norm;
            obj->vtx[n].nZ = obj->vtx[n].Z / norm;
            n++;

            lVR = vR + space;
            lHR = hR + space;
            obj->vtx[n].X = R * sin(lHR / 180 * M_PI) * sin(lVR / 180 * M_PI);
            obj->vtx[n].Y = R * cos(lHR / 180 * M_PI) * sin(lVR / 180 * M_PI);
            obj->vtx[n].Z = R * cos(lVR / 180 * M_PI);
            obj->vtx[n].V = lVR / 180;
            obj->vtx[n].U = lHR / 360;
            norm = sqrt(obj->vtx[n].X * obj->vtx[n].X + obj->vtx[n].Y * obj->vtx[n].Y + obj->vtx[n].Z * obj->vtx[n].Z);
            obj->vtx[n].nX = obj->vtx[n].X / norm;
            obj->vtx[n].nY = obj->vtx[n].Y / norm;
            obj->vtx[n].nZ = obj->vtx[n].Z / norm;
            n++;
        }
    }
    return obj;
}
float Geometries::toRad(float theta)
{
    return theta * 0.0174533;
}

void Geometries::CreateSolidCube(double width, double height, double depth, COLOR color)
{
    GLfloat materialEmission[] = {0.00, 0.00, 0.00, 1.0};
    GLfloat materialColor[] = {1.0, 1.0, 0.0, 1.0};
    GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_shininess[] = {128};

    glPushMatrix();

    glMaterialfv(GL_FRONT, GL_EMISSION, materialEmission);
    glMaterialfv(GL_FRONT, GL_AMBIENT, materialColor);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, materialColor);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glColor3f(color.R, color.G, color.B);

    glScalef(width, height, depth);
    glutSolidCube(1.0);

    glPopMatrix();
}

void Geometries::CreateSolidSphere(double radius, COLOR color)
{
    GLfloat materialEmission[] = {0.00, 0.00, 0.00, 1.0};
    GLfloat materialColor[] = {1.0, 1.0, 0.0, 1.0};
    GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_shininess[] = {128};

    glPushMatrix();

    glMaterialfv(GL_FRONT, GL_EMISSION, materialEmission);
    glMaterialfv(GL_FRONT, GL_AMBIENT, materialColor);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, materialColor);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glColor3f(color.R, color.G, color.B);

    glutSolidSphere(radius, 20, 10);

    glPopMatrix();
}
