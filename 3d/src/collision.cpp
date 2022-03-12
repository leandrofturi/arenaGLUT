#include <math.h>
#include "../include/collision.h"
#include "../include/geometries.h"

bool Collision::bump(Puppet *puppet, Block *block, GLfloat aW, GLfloat aH)
{
    GLfloat x1 = puppet->getX();
    GLfloat y1 = puppet->getY();
    GLfloat z1 = puppet->getZ();
    GLfloat w1 = puppet->getWidth();
    GLfloat h1 = puppet->getHeight();
    GLfloat d1 = puppet->getDepth();

    GLfloat x2 = -block->getZ();
    GLfloat y2 = block->getY();
    GLfloat z2 = -block->getX();
    GLfloat w2 = aH / 2.0;
    GLfloat h2 = block->getHeight();
    GLfloat d2 = block->getWidth();

    bool collisionX = x1 - w1 >= x2 && x2 + w2 > x1;
    bool collisionY = y2 + h2 < y1;

    printf("%.2lf\t%.2lf\t%.2lf\t%.2lf\t%.2lf\t%.2lf\n", x1, y1, z1, w1, h1, d1);
    printf("%.2lf\t%.2lf\t%.2lf\t%.2lf\t%.2lf\t%.2lf\n", x2, y2, z2, w2, h2, d2);
    printf("%d\n\n", collisionY);
    // bool collisionY = y1 + h1 >= y2 && y2 + h2 >= y1;
    // bool collisionZ = z1 + d1 <= z2 && d2 + d2 <= z1;

    return collisionX;
}

bool Collision::bump(Puppet *puppet, std::list<Block *> blocks, GLfloat aW, GLfloat aH)
{
    for (std::list<Block *>::iterator it = blocks.begin(); it != blocks.end(); ++it)
    {
        if (bump(puppet, (*it), aW, aH))
        {
            return true;
        }
    }
    return false;
}

//

bool Collision::collision(Puppet *puppet, Arena *arena)
{
    return bump(puppet, arena->blocks, arena->getWidth(), arena->getHeight());
}
