#include "../include/collision.h"

int Collision::bumpTop(Puppet *puppet, Block *block)
{
    if (!puppet->isFlying())
    {
        return 0;
    }

    GLfloat x1 = puppet->getX();
    GLfloat y1 = puppet->getY();
    GLfloat w1 = puppet->getWidth();
    GLfloat h1 = puppet->getHeight();

    GLfloat x2 = block->getX();
    GLfloat y2 = block->getY();
    GLfloat w2 = block->getWidth();
    GLfloat h2 = block->getHeight();

    return ((y1 - h1) <= (y2 + h2)) && (y1 >= y2) && (x1 >= x2) && (x1 <= (x2 + w2));
}

int Collision::bumpTop(Puppet *puppet, std::list<Block *> blocks)
{
    for (std::list<Block *>::iterator it = blocks.begin(); it != blocks.end(); ++it)
    {
        if (bumpTop(puppet, (*it)))
        {
            puppet->cover((*it)->getY() + (*it)->getHeight());
            return true;
        }
    }
    puppet->uncover();
    return false;
}

int Collision::bumpBottom(Puppet *puppet, Block *block)
{
    if (!puppet->isFalling())
    {
        return 0;
    }

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

int Collision::bumpFront(Puppet *puppet, Block *block)
{
    GLfloat x1 = puppet->getX();
    GLfloat y1 = puppet->getY();
    GLfloat w1 = puppet->getWidth();
    GLfloat h1 = puppet->getHeight();

    GLfloat x2 = block->getX();
    GLfloat y2 = block->getY();
    GLfloat w2 = block->getWidth();
    GLfloat h2 = block->getHeight();

    return (y1 > (y2 + h2)) && ((y1 - h1) < y2) && ((x1 + w1 / 2.0) > x2) && ((x1 + w1 / 2.0) < (x2 + w2));
}

int Collision::bumpFront(Puppet *puppet, std::list<Block *> blocks)
{
    for (std::list<Block *>::iterator it = blocks.begin(); it != blocks.end(); ++it)
    {
        if (bumpFront(puppet, (*it)))
        {
            puppet->stop(1);
            return true;
        }
    }
    puppet->stop(0);
    return false;
}

int Collision::bumpBack(Puppet *puppet, Block *block)
{
    GLfloat x1 = puppet->getX();
    GLfloat y1 = puppet->getY();
    GLfloat w1 = puppet->getWidth();
    GLfloat h1 = puppet->getHeight();

    GLfloat x2 = block->getX();
    GLfloat y2 = block->getY();
    GLfloat w2 = block->getWidth();
    GLfloat h2 = block->getHeight();

    return (y1 > (y2 + h2)) && ((y1 - h1) < y2) && ((x1 - w1 / 2.0) < (x2 + w2)) && ((x1 - w1 / 2.0) > x2);
}

int Collision::bumpBack(Puppet *puppet, std::list<Block *> blocks)
{
    for (std::list<Block *>::iterator it = blocks.begin(); it != blocks.end(); ++it)
    {
        if (bumpBack(puppet, (*it)))
        {
            puppet->stop(-1);
            return true;
        }
    }
    puppet->stop(0);
    return false;
}

//

int Collision::bump(Puppet *puppet, Gunshot *gunshot)
{
    GLfloat x1 = puppet->getX();
    GLfloat y1 = puppet->getY();
    GLfloat w1 = puppet->getWidth();
    GLfloat h1 = puppet->getHeight();

    GLfloat x2 = gunshot->getX();
    GLfloat y2 = gunshot->getY();
    GLfloat r2 = gunshot->getRadius();

    return ((y1 - h1) <= (y2 - r2)) && (y1 >= (y2 + r2)) && ((x1 + w1 / 2.0) >= (x2 - r2)) && ((x1 - w1 / 2.0) <= (x2 + r2));
}

//

int Collision::bumpTop(Puppet *puppet, Opponent *opponent)
{
    if (!puppet->isFlying())
    {
        return 0;
    }

    GLfloat x1 = puppet->getX();
    GLfloat y1 = puppet->getY();
    GLfloat w1 = puppet->getWidth();
    GLfloat h1 = puppet->getHeight();

    GLfloat x2 = opponent->getX();
    GLfloat y2 = opponent->getY();
    GLfloat r2 = opponent->getRadius();

    return ((y1 - h1) <= (y2 + r2)) && (y1 >= y2) && (x1 >= x2) && (x1 <= (x2 + r2));
}

int Collision::bumpTop(Puppet *puppet, std::list<Opponent *> opponents)
{
    for (std::list<Opponent *>::iterator it = opponents.begin(); it != opponents.end(); ++it)
    {
        if (bumpTop(puppet, (*it)))
        {
            puppet->cover((*it)->getY() + (*it)->getRadius());
            return true;
        }
    }
    puppet->uncover();
    return false;
}

int Collision::bumpBottom(Puppet *puppet, Opponent *opponent)
{
    if (!puppet->isFalling())
    {
        return 0;
    }

    GLfloat x1 = puppet->getX();
    GLfloat y1 = puppet->getY();
    GLfloat w1 = puppet->getWidth();
    GLfloat h1 = puppet->getHeight();

    GLfloat x2 = opponent->getX();
    GLfloat y2 = opponent->getY();
    GLfloat r2 = opponent->getRadius();

    return (y1 >= y2) && (y1 <= (y2 + r2)) && (x1 >= x2) && (x1 <= (x2 + r2));
}

int Collision::bumpBottom(Puppet *puppet, std::list<Opponent *> opponents)
{
    for (std::list<Opponent *>::iterator it = opponents.begin(); it != opponents.end(); ++it)
    {
        if (bumpBottom(puppet, (*it)))
        {
            puppet->elevate((*it)->getY() + (*it)->getRadius());
            return true;
        }
    }
    puppet->shootDown();
    return false;
}

int Collision::bumpFront(Puppet *puppet, Opponent *opponent)
{
    GLfloat x1 = puppet->getX();
    GLfloat y1 = puppet->getY();
    GLfloat w1 = puppet->getWidth();
    GLfloat h1 = puppet->getHeight();

    GLfloat x2 = opponent->getX();
    GLfloat y2 = opponent->getY();
    GLfloat r2 = opponent->getRadius();

    return ((y1 - h1) <= (y2 - r2)) && (y1 >= (y2 + r2)) && ((x1 + w1 / 2.0) >= (x2 - r2)) && ((x1 - w1 / 2.0) <= (x2 + r2));
}

int Collision::bumpFront(Puppet *puppet, std::list<Opponent *> opponents)
{
    for (std::list<Opponent *>::iterator it = opponents.begin(); it != opponents.end(); ++it)
    {
        if (bumpFront(puppet, (*it)))
        {
            puppet->stop(1);
            return true;
        }
    }
    puppet->stop(0);
    return false;
}

int Collision::bumpBack(Puppet *puppet, Opponent *opponent)
{
    GLfloat x1 = puppet->getX();
    GLfloat y1 = puppet->getY();
    GLfloat w1 = puppet->getWidth();
    GLfloat h1 = puppet->getHeight();

    GLfloat x2 = opponent->getX();
    GLfloat y2 = opponent->getY();
    GLfloat r2 = opponent->getRadius();

    return ((y1 - h1) <= (y2 - r2)) && (y1 >= (y2 + r2)) && ((x1 + w1 / 2.0) >= (x2 - r2)) && ((x1 - w1 / 2.0) <= (x2 + r2));
}

int Collision::bumpBack(Puppet *puppet, std::list<Opponent *> opponents)
{
    for (std::list<Opponent *>::iterator it = opponents.begin(); it != opponents.end(); ++it)
    {
        if (bumpBack(puppet, (*it)))
        {
            puppet->stop(-1);
            return true;
        }
    }
    puppet->stop(0);
    return false;
}

//

int Collision::bumpGunshot(Puppet *puppet, std::list<Opponent *> opponents)
{
    for (std::list<Opponent *>::iterator it = opponents.begin(); it != opponents.end(); ++it)
    {
        for (std::list<Gunshot *>::iterator gs = (*it)->gunshots.begin(); gs != (*it)->gunshots.end(); ++gs)
        {
            if (bump(puppet, (*gs)))
            {
                puppet->kill();
                return true;
            }
        }
    }
    return false;
}

//

void Collision::handleCollision(Puppet *puppet, std::list<Block *> blocks, std::list<Opponent *> opponents)
{
    if (!bumpTop(puppet, blocks))
    {
        if (!bumpBottom(puppet, blocks))
        {
            if (!bumpFront(puppet, blocks))
            {
                if (!bumpBack(puppet, blocks))
                {
                    if (!bumpTop(puppet, opponents))
                    {
                        if (!bumpBottom(puppet, opponents))
                        {
                            if (!bumpFront(puppet, opponents))
                            {
                                if (!bumpBack(puppet, opponents))
                                    ;
                            }
                        }
                    }
                }
            }
        }
    }

    if (bumpGunshot(puppet, opponents))
        ;
}
