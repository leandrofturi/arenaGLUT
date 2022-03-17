#include <math.h>
#include "../include/collision.h"
#include "../include/geometries.h"

int i = 0;
int bompBottom = 0;

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
    bool collisionY = y1 + h1 >= y2 - h2 && y1 <= y2;
    bool collisionZ = z1 - d1 <= z2 && z2 - d2 < z1 + d1;

    if (collisionX && collisionY && collisionZ && fabs(y1 - y2) <= 0.1 * y1)
        bompBottom = 1;
    else
        bompBottom = 0;

    return collisionX && collisionY && collisionZ;
}

bool Collision::bump(Puppet *puppet, std::list<Block *> blocks)
{
    for (std::list<Block *>::iterator it = blocks.begin(); it != blocks.end(); ++it)
    {
        if (bump(puppet, (*it)))
        {
            if (bompBottom)
                puppet->elevate(true);
            return true;
        }
    }
    puppet->elevate(false);
    return false;
}

bool Collision::bump(Puppet *puppet, Gunshot *gunshot)
{
    GLfloat x1 = puppet->getX();
    GLfloat y1 = puppet->getY();
    GLfloat z1 = puppet->getZ();
    GLfloat w1 = puppet->getWidth();
    GLfloat h1 = puppet->getHeight();
    GLfloat d1 = puppet->getDepth();

    GLfloat x2 = -gunshot->getZ();
    GLfloat y2 = gunshot->getY();
    GLfloat z2 = gunshot->getX();
    GLfloat w2 = gunshot->getWidth();
    GLfloat h2 = gunshot->getHeight();
    GLfloat d2 = gunshot->getDepth();

    bool collisionX = x1 + w1 >= x2 && x2 + w2 >= x1;
    bool collisionY = y1 + h1 >= y2 - h2 && y1 <= y2;
    bool collisionZ = z1 - d1 <= z2 && z2 - d2 < z1 + d1;

    return collisionX && collisionY && collisionZ;
}

bool Collision::bump(Gunshot *gunshot, Block *block)
{
    GLfloat x1 = -gunshot->getX();
    GLfloat y1 = gunshot->getY();
    GLfloat z1 = -gunshot->getZ();
    GLfloat w1 = gunshot->getWidth();
    GLfloat h1 = gunshot->getHeight();
    GLfloat d1 = gunshot->getDepth();

    GLfloat x2 = block->getX();
    GLfloat y2 = block->getY();
    GLfloat z2 = block->getZ();
    GLfloat w2 = block->getWidth();
    GLfloat h2 = block->getHeight();
    GLfloat d2 = block->getDepth();

    bool collisionX = x1 - w1 >= x2 && x2 + w2 > x1;
    bool collisionY = y1 >= y2 - h2 && y1 <= y2;
    bool collisionZ = z1 - d1 <= z2 && z2 - d2 < z1 + d1;

    return collisionX && collisionY && collisionZ;
}

bool Collision::bump(Puppet *puppet, Opponent *opponent)
{
    GLfloat x1 = puppet->getX();
    GLfloat y1 = puppet->getY();
    GLfloat z1 = puppet->getZ();
    GLfloat w1 = puppet->getWidth();
    GLfloat h1 = puppet->getHeight();
    GLfloat d1 = puppet->getDepth();

    GLfloat x2 = opponent->getX();
    GLfloat y2 = opponent->getY();
    GLfloat z2 = opponent->getZ();
    GLfloat w2 = opponent->getWidth();
    GLfloat h2 = opponent->getHeight();
    GLfloat d2 = opponent->getDepth();

    bool collisionX = x1 <= x2 + w2 && x1 + w1 >= x2;
    bool collisionY = y1 <= y2 + h2 && y1 + h1 >= y2;
    bool collisionZ = z1 - d1 <= z2 && z2 - d2 < z1 + d1;

    return collisionX && collisionY && collisionZ;
}

bool Collision::bump(Opponent *opponent, Gunshot *gunshot)
{
    GLfloat x1 = opponent->getX();
    GLfloat y1 = opponent->getY();
    GLfloat z1 = opponent->getZ();
    GLfloat w1 = opponent->getWidth();
    GLfloat h1 = opponent->getHeight();
    GLfloat d1 = opponent->getDepth();

    GLfloat x2 = -gunshot->getZ();
    GLfloat y2 = gunshot->getY();
    GLfloat z2 = gunshot->getX();
    GLfloat w2 = gunshot->getWidth();
    GLfloat h2 = gunshot->getHeight();
    GLfloat d2 = gunshot->getDepth();

    bool collisionX = x1 + w1 >= x2 && x2 + w2 >= x1;
    bool collisionY = y1 + h1 >= y2 - h2 && y1 <= y2;
    bool collisionZ = z1 - d1 <= z2 && z2 - d2 < z1 + d1;

    // printf("%.2f")

    return collisionX && collisionY && collisionZ;
}

bool Collision::bump(Puppet *puppet, std::list<Gunshot *> gunshots, std::list<Opponent *> opponnets, std::list<Block *> blocks)
{
    for (std::list<Gunshot *>::iterator it = gunshots.begin(); it != gunshots.end(); ++it)
    {
        if (bump(puppet, (*it)))
        {
            puppet->kill();
            return true;
        }

        for (std::list<Block *>::iterator jt = blocks.begin(); jt != blocks.end(); ++jt)
        {
            if (bump((*it), (*jt)))
            {
                (*it)->bump();
            }
        }

        for (std::list<Opponent *>::iterator jt = opponnets.begin(); jt != opponnets.end();)
        {
            if (bump(puppet, (*jt)))
            {
                (*jt)->setDirection(-(*jt)->getWalkDir());
                puppet->bumpOpponent(true);
                puppet->elevate(true);
                return true;
            }

            if (bump((*jt), (*it)))
            {
                (*it)->bump();
                jt = opponnets.erase(jt);
                // (*jt)->kill();
                // return true;
            }
            else
            {
                ++jt;
            }
        }
        puppet->bumpOpponent(false);
        puppet->elevate(false);
    }

    return false;
}

//

bool Collision::collision(Puppet *puppet, Arena *arena)
{
    if (bump(puppet, arena->gunshots, arena->opponents, arena->blocks))
        ;
    return bump(puppet, arena->blocks);
}
