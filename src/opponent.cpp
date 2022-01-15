#include "../include/opponent.h"
#include "../include/geometries.h"

void Opponent::drawOpponent(GLfloat x, GLfloat y)
{
    glPushMatrix();

    glTranslatef(x, y, 0.0);
    Geometries::drawCircle(gRadius, gR, gG, gB);

    glPopMatrix();
}
