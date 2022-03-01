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

    bool bump(Puppet *puppet, Gunshot *gunshot);

    bool bumpBottom(Puppet *puppet, Opponent *opponent);
    bool bumpBottom(Puppet *puppet, std::list<Opponent *> *opponents);
    bool bumpFront(Puppet *puppet, Opponent *opponent);
    bool bumpFront(Puppet *puppet, std::list<Opponent *> *opponents);
    bool bumpBack(Puppet *puppet, Opponent *opponent);
    bool bumpBack(Puppet *puppet, std::list<Opponent *> *opponents);

    bool bumpGunshot(Puppet *puppet, std::list<Opponent *> *opponents);

    bool bumpOpponent(Gunshot *gunshot, Opponent *opponent);
    void bumpOpponent(std::list<Gunshot *> *gunshots, std::list<Opponent *> *opponents);

    bool bumpBlock(Gunshot *gunshot, Block *block);
    void bumpBlock(std::list<Gunshot *> *gunshots, std::list<Block *> blocks);

    void handleCollision(Puppet *puppet, std::list<Block *> blocks, std::list<Opponent *> *opponents, std::list<Gunshot *> *gunshots);
}

#endif /* COLLISION_H */
