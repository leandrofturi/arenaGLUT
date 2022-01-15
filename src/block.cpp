#include "../include/block.h"
#include "../include/geometries.h"

void Block::drawBlock(GLfloat x, GLfloat y)
{
    glPushMatrix();

    glTranslatef(x, y, 0.0);
    Geometries::drawRect(gHeight, gWidth, gR, gG, gB);

    glPopMatrix();
}
