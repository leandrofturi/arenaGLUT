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
    bool bump(Puppet *puppet, Gunshot *gunshot);
    bool bump(Puppet *puppet, Opponent *opponent);
    bool bump(Opponent *opponent, Gunshot *gunshot);
    bool bump(Gunshot *gunshot, Block *block);
    bool bump(Puppet *puppet, std::list<Gunshot *> gunshots, std::list<Opponent *> opponnets, std::list<Block *> blocks);

    bool collision(Puppet *puppet, Arena *arena);
}

#endif /* COLLISION_H */
