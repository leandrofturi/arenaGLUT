#ifndef OPPONENT_H
#define OPPONENT_H
#include <GL/gl.h>
#include <GL/glu.h>
#include <list>
#include <math.h>
#include "gunshot.h"
#include "block.h"

class Opponent
{
    GLfloat gX;
    GLfloat gY;
    GLfloat gX0;
    GLfloat gY0;
    GLfloat gRadius;
    GLfloat gR;
    GLfloat gG;
    GLfloat gB;
    GLfloat gSpeed = 2.5;

    GLfloat ArenaWidth = 500.0;
    GLfloat ArenaHeight = 500.0;

    GLfloat gXLim[2];

    double walkDirection = ((double)rand() / (RAND_MAX)) * 2.0 - 1.0; // -1: left, 1: right

    int alive = 1; // 1: yes, 0: no

public:
    std::list<Gunshot *> gunshots;

private:
    void drawOpponent(GLfloat x, GLfloat y);
    Gunshot *takeShoot(GLfloat x, GLfloat y);
    void takeMoviment();

public:
    Opponent(GLfloat x, GLfloat y, GLfloat radius, GLfloat R, GLfloat G, GLfloat B)
    {
        gX = x;
        gY = y;
        gX0 = x;
        gY0 = y;
        gRadius = radius;
        gR = R;
        gG = G;
        gB = B;
    };
    void draw()
    {
        if (alive)
            drawOpponent(gX, gY);
    };
    void setInitial(std::list<Block *> *blocks, GLfloat x, GLfloat y, GLfloat arenaWidth, GLfloat arenaHeight);
    GLfloat getX()
    {
        return gX;
    };
    GLfloat getY()
    {
        return gY;
    };
    GLfloat getRadius()
    {
        return gRadius;
    };
    void shot(GLfloat x, GLfloat y)
    {
        if (alive)
        {
            Gunshot *s = takeShoot(x, y);
            s->draw();
            gunshots.push_back(s);
        }
    };
    void changeDirection(int dir)
    {
        walkDirection = dir;
    }
    void move()
    {
        if (alive)
        {
            takeMoviment();
        }
    };
    int isAlive()
    {
        return alive == 1;
    }
    void kill()
    {
        alive = 0;
    }
    void reset()
    {
        gX = gX0;
        gY = gY0;

        walkDirection = ((double)rand() / (RAND_MAX)) * 2.0 - 1.0;

        alive = 1;
    }
};

#endif /* OPPONENT_H */
