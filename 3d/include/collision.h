#ifndef COLLISION_H
#define COLLISION_H
#include <GL/gl.h>
#include <GL/glu.h>
#include <list>
#include "puppet.h"
#include "block.h"
#include "opponent.h"
#include "gunshot.h"
#include "arena.h"

namespace Collision
{
    bool bump(Puppet *puppet, Block *block);
    bool bump(Puppet *puppet, std::list<Block *> blocks);

    bool collision(Puppet *puppet, Arena *arena);
}

#endif /* COLLISION_H */
