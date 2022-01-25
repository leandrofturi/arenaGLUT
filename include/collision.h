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
    int bumpTop(Puppet *puppet, Block *block);
    int bumpTop(Puppet *puppet, std::list<Block *> blocks);
    int bumpBottom(Puppet *puppet, Block *block);
    int bumpBottom(Puppet *puppet, std::list<Block *> blocks);
    int bumpFront(Puppet *puppet, Block *block);
    int bumpFront(Puppet *puppet, std::list<Block *> blocks);
    int bumpBack(Puppet *puppet, Block *block);
    int bumpBack(Puppet *puppet, std::list<Block *> blocks);

    int bump(Puppet *puppet, Gunshot *gunshot);

    int bumpTop(Puppet *puppet, Opponent *opponent);
    int bumpTop(Puppet *puppet, std::list<Opponent *> opponents);
    int bumpBottom(Puppet *puppet, Opponent *opponent);
    int bumpBottom(Puppet *puppet, std::list<Opponent *> opponents);
    int bumpFront(Puppet *puppet, Opponent *opponent);
    int bumpFront(Puppet *puppet, std::list<Opponent *> opponents);
    int bumpBack(Puppet *puppet, Opponent *opponent);
    int bumpBack(Puppet *puppet, std::list<Opponent *> opponents);

    int bumpGunshot(Puppet *puppet, std::list<Opponent *> opponents);

    void handleCollision(Puppet *puppet, std::list<Block *> blocks, std::list<Opponent *> opponents);
}

#endif /* COLLISION_H */
