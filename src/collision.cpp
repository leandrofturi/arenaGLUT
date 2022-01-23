#include "../include/collision.h"

int Collision::bumpBottom(Puppet *puppet, Block *block)
{
    GLfloat x1 = puppet->getX();
    GLfloat y1 = puppet->getY();
    GLfloat w1 = puppet->getWidth();
    GLfloat h1 = puppet->getHeight();

    GLfloat x2 = block->getX();
    GLfloat y2 = block->getY();
    GLfloat w2 = block->getWidth();
    GLfloat h2 = block->getHeight();

    return (y1 >= y2) && (y1 <= (y2 + h2)) && (x1 >= x2) && (x1 <= (x2 + w2));
}

int Collision::bumpBottom(Puppet *puppet, std::list<Block *> blocks)
{
    for (std::list<Block *>::iterator it = blocks.begin(); it != blocks.end(); ++it)
    {
        if (bumpBottom(puppet, (*it)))
        {
            puppet->elevate((*it)->getY());
            return true;
        }
    }
    puppet->shootDown();
    return false;
}

void Collision::handleCollision(Puppet *puppet, std::list<Block *> blocks)
{
    bumpBottom(puppet, blocks);
}