#include "../include/block.h"
#include "../include/geometries.h"

void Block::draw()
{
    glPushMatrix();

    glTranslatef(gX, gY, gZ);
    Geometries::CreateSolidCube(gWidth, gHeight, gDepth, COLOR{0.0, 0.0, 0.0});

    glPopMatrix();


    glPushMatrix();

    glTranslatef(getX(), getY(), getZ());
    Geometries::CreateSolidSphere(1, COLOR{0.0, 0.0, 0.0});

    glPushMatrix();
    // glTranslatef(0, 0, -45.83);
    Geometries::CreateSolidSphere(1, COLOR{0.0, 0.0, 0.0});
    glPopMatrix();

    glPushMatrix();
    glTranslatef(10, 0, 0);
    Geometries::CreateSolidSphere(1, COLOR{0.0, 0.0, 0.0});
    glPopMatrix();

    glPopMatrix();
}
