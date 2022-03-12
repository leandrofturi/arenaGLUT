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
    bool bump(Puppet *puppet, Block *block, GLfloat aW, GLfloat aH);
    bool bump(Puppet *puppet, std::list<Block *> blocks, GLfloat aW, GLfloat aH);

    bool collision(Puppet *puppet, Arena *arena);
}

#endif /* COLLISION_H */
