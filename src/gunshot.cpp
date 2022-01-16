#include "../include/gunshot.h"
#include "../include/geometries.h"
#include <math.h>
#include <stdlib.h>

#define maxDistance 500
#define radiusGunshot 4.8

void Gunshot::drawGunshot(GLfloat x, GLfloat y)
{
    glPushMatrix();

    glTranslatef(x, y, 0.0);
    Geometries::drawCircle(radiusGunshot, ((double) rand() / (RAND_MAX)) , ((double) rand() / (RAND_MAX)), ((double) rand() / (RAND_MAX)));

    glPopMatrix();
}

void Gunshot::move()
{
    gX = gX + cos(Geometries::toRad(gDirectionAng)) * gSpeed;
    gY = gY + sin(Geometries::toRad(gDirectionAng)) * gSpeed;
}

bool Gunshot::valid()
{
    return fmax(fabs(gX - gXInit), fabs(gY - gYInit)) < maxDistance;
}
