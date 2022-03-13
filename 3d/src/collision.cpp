#include <math.h>
#include "../include/collision.h"
#include "../include/geometries.h"

bool Collision::bump(Puppet *puppet, Block *block)
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
    GLfloat w2 = block->getDepth();
    GLfloat h2 = block->getHeight();
    GLfloat d2 = block->getWidth();

    bool collisionX = x1 - w1 >= x2 && x2 + w2 > x1;
    bool collisionY = y1 + h1 >= y2 && y1 <= y2;
    bool collisionZ = z1 - d1 <= z2 && z2 - d2 < z1 + d1;

    return collisionX && collisionY && collisionZ;
}

bool Collision::bump(Puppet *puppet, std::list<Block *> blocks)
{
    for (std::list<Block *>::iterator it = blocks.begin(); it != blocks.end(); ++it)
    {
        if (bump(puppet, (*it)))
        {
            puppet->elevate(true);
            return true;
        }
    }
    puppet->elevate(false);
    return false;
}

//

bool Collision::collision(Puppet *puppet, Arena *arena)
{
    return bump(puppet, arena->blocks);
}
