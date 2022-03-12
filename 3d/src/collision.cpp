#include "../include/collision.h"
#include "../include/geometries.h"

int isBumped = 0;

bool Collision::bumpTop(Puppet *puppet, Block *block)
{
    GLfloat x1 = puppet->getX();
    GLfloat y1 = puppet->getY();
    GLfloat w1 = puppet->getWidth();
    GLfloat h1 = puppet->getHeight();

    GLfloat x2 = block->getX();
    GLfloat y2 = block->getY();
    GLfloat w2 = block->getWidth();
    GLfloat h2 = block->getHeight();

    return ((y1 - h1) <= (y2 + h2)) && (y1 >= y2) && ((x1 + w1 / 2.0) >= x2) && ((x1 - w1 / 2.0) <= (x2 + w2));
}

bool Collision::bumpTop(Puppet *puppet, std::list<Block *> blocks)
{
    if (puppet->isFlying())
    {
        for (std::list<Block *>::iterator it = blocks.begin(); it != blocks.end(); ++it)
        {
            if (bumpTop(puppet, (*it)))
            {
                puppet->cover((*it)->getY() + (*it)->getHeight());
                isBumped = 1;
                return true;
            }
        }
    }
    puppet->uncover();
    isBumped = 0;
    return false;
}

bool Collision::bumpBottom(Puppet *puppet, Block *block)
{
    GLfloat x1 = puppet->getX();
    GLfloat y1 = puppet->getY();
    GLfloat w1 = puppet->getWidth();
    GLfloat h1 = puppet->getHeight();

    GLfloat x2 = block->getX();
    GLfloat y2 = block->getY();
    GLfloat w2 = block->getWidth();
    GLfloat h2 = block->getHeight();

    return (y1 <= (y2 + h2)) && (y1 >= y2) && ((x1 + w1 / 2.0) >= x2) && ((x1 - w1 / 2.0) <= (x2 + w2));
}

bool Collision::bumpBottom(Puppet *puppet, std::list<Block *> blocks)
{
    if (puppet->isFalling())
    {
        for (std::list<Block *>::iterator it = blocks.begin(); it != blocks.end(); ++it)
        {
            if (bumpBottom(puppet, (*it)))
            {
                if (puppet->getY() + 1 >= (*it)->getY())
                {
                    puppet->elevate((*it)->getY());
                }
                isBumped = 1;
                return true;
            }
        }
    }
    puppet->shootDown();
    isBumped = 0;
    return false;
}

bool Collision::bumpFront(Puppet *puppet, Block *block)
{
    GLfloat x1 = puppet->getX();
    GLfloat y1 = puppet->getY();
    GLfloat w1 = puppet->getWidth();
    GLfloat h1 = puppet->getHeight();

    GLfloat x2 = block->getX();
    GLfloat y2 = block->getY();
    GLfloat w2 = block->getWidth();
    GLfloat h2 = block->getHeight();

    return ((x1 + w1 / 2.0) >= (x2 - 1)) && ((x1 - w1 / 2.0) <= (x2 + w2)) && !((y1 - 1 - h1) >= (y2 + h2)) && !(((y1 - 1) <= y2));
}

bool Collision::bumpFront(Puppet *puppet, std::list<Block *> blocks)
{
    if (puppet->getDirection() == 1)
    {
        for (std::list<Block *>::iterator it = blocks.begin(); it != blocks.end(); ++it)
        {
            if (bumpFront(puppet, (*it)))
            {
                puppet->stop(1);
                isBumped = 1;
                return true;
            }
        }
    }
    puppet->stop(0);
    isBumped = 0;
    return false;
}

bool Collision::bumpBack(Puppet *puppet, Block *block)
{
    GLfloat x1 = puppet->getX();
    GLfloat y1 = puppet->getY();
    GLfloat w1 = puppet->getWidth();
    GLfloat h1 = puppet->getHeight();

    GLfloat x2 = block->getX();
    GLfloat y2 = block->getY();
    GLfloat w2 = block->getWidth();
    GLfloat h2 = block->getHeight();

    return ((x1 - w1 / 2.0) <= (x2 + w2 + 1)) && ((x1 + w1 / 2.0) >= x2) && !((y1 - 1 - h1) >= (y2 + h2)) && !(((y1 - 1) <= y2));
}

bool Collision::bumpBack(Puppet *puppet, std::list<Block *> blocks)
{
    if (puppet->getDirection() == -1)
    {
        for (std::list<Block *>::iterator it = blocks.begin(); it != blocks.end(); ++it)
        {
            if (bumpBack(puppet, (*it)))
            {
                puppet->stop(-1);
                isBumped = 1;
                return true;
            }
        }
    }
    puppet->stop(0);
    isBumped = 0;
    return false;
}

//

void Collision::handleCollision(Puppet *puppet, std::list<Block *> blocks, std::list<Opponent *> *opponents, std::list<Gunshot *> *gunshots)
{
    if (!bumpFront(puppet, blocks))
    {
        if (!bumpBack(puppet, blocks))
            ;
    }

    if (!bumpTop(puppet, blocks))
    {
        if (!bumpBottom(puppet, blocks))
            ;
    }
}
