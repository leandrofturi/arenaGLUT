#ifndef COLLISION_H
#define COLLISION_H
#include <GL/gl.h>
#include <GL/glu.h>
#include <list>
#include "puppet.h"
#include "block.h"
#include "opponent.h"
#include "gunshot.h"

namespace Collision
{
    bool bumpTop(Puppet *puppet, Block *block);
    bool bumpTop(Puppet *puppet, std::list<Block *> blocks);
    bool bumpBottom(Puppet *puppet, Block *block);
    bool bumpBottom(Puppet *puppet, std::list<Block *> blocks);
    bool bumpFront(Puppet *puppet, Block *block);
    bool bumpFront(Puppet *puppet, std::list<Block *> blocks);
    bool bumpBack(Puppet *puppet, Block *block);
    bool bumpBack(Puppet *puppet, std::list<Block *> blocks);

    void handleCollision(Puppet *puppet, std::list<Block *> blocks);
}

#endif /* COLLISION_H */
