#ifndef COLLISION_H
#define COLLISION_H
#include <GL/gl.h>
#include <GL/glu.h>
#include <list>
#include "puppet.h"
#include "block.h"

namespace Collision
{
    int bumpBottom(Puppet *puppet, Block *block);
    int bumpBottom(Puppet *puppet, std::list<Block *> blocks);
    void handleCollision(Puppet *puppet, std::list<Block *> blocks);
}

#endif /* COLLISION_H */
