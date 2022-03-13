#include "../include/block.h"
#include "../include/geometries.h"

void Block::draw()
{
    glPushMatrix();

    glTranslatef(-gX, gY, -gZ);
    Geometries::CreateSolidCube(gWidth, gHeight, gDepth, COLOR{0.0, 0.0, 0.0});

    glPopMatrix();
}
