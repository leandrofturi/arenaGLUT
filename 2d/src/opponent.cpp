#include "../include/opponent.h"
#include "../include/geometries.h"
#include <math.h>
#include <iostream>

void Opponent::drawOpponent(GLfloat x, GLfloat y)
{
    glPushMatrix();

    glTranslatef(x, y, 0.0);
    Geometries::drawCircle(gRadius, gR, gG, gB);

    glPopMatrix();
}

Gunshot *Opponent::takeShoot(GLfloat x, GLfloat y)
{
    GLfloat directionAng = Geometries::toDegree(atan2(y - gX, x - gX));
    if (gY < y) {
        directionAng *= -1;
    }

    Gunshot *shot = new Gunshot(gX, gY, directionAng, 2.0 * gSpeed);
    return shot;
}

void Opponent::takeMoviment()
{
    if (((gX - gRadius - gSpeed) <= gXLim[0]) || ((gX + gRadius + gSpeed) >= gXLim[1]))
    {
        walkDirection *= -1;
    }
    gX += gSpeed * walkDirection;
}

void Opponent::setInitial(std::list<Block *> *blocks, GLfloat x, GLfloat y, GLfloat arenaWidth, GLfloat arenaHeight)
{
    gX += x;
    gY += y;
    gXLim[0] = 0;
    gXLim[1] = arenaWidth;

    ArenaWidth = arenaWidth;
    ArenaHeight = arenaHeight;

    for (std::list<Block *>::iterator it = blocks->begin(); it != blocks->end(); ++it)
    {
        GLfloat x = (*it)->getX();
        GLfloat y = (*it)->getY();
        GLfloat w = (*it)->getWidth();
        GLfloat h = (*it)->getHeight();

        if ((gX >= x) && (gX <= (x + w)) && ((gY + gRadius * 1.2) >= y) && (gY <= y))
        {
            gXLim[0] = x;
            gXLim[1] = x + w;
            return;
        }
        if ((gX >= (x + w)) && ((gX - gXLim[0]) > (gX - x - w)) && (gY >= y) && (gY <= (y + h)))
        {
            gXLim[0] = x + w;
        }
        if ((gX <= x) && ((gXLim[1] - gX) > (x - gX)) && (gY >= y) && (gY <= (y + h)))
        {
            gXLim[1] = x;
        }
    }
}