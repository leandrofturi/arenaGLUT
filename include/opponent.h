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
    GLfloat gRadius;
    GLfloat gR;
    GLfloat gG;
    GLfloat gB;
    GLfloat gSpeed = 2.5;

    GLfloat gXLim[2];

    double walkDirection = ((double)rand() / (RAND_MAX)) * 2.0 - 1.0; // -1: left, 1: right

public:
    std::list<Gunshot *> gunshots;

private:
    void drawOpponent(GLfloat x, GLfloat y);
    Gunshot *takeShoot();
    void takeMoviment();

public:
    Opponent(GLfloat x, GLfloat y, GLfloat radius, GLfloat R, GLfloat G, GLfloat B)
    {
        gX = x;
        gY = y;
        gRadius = radius;
        gR = R;
        gG = G;
        gB = B;
    };
    void draw()
    {
        drawOpponent(gX, gY);
    };
    void setInitial(std::list<Block *> *blocks, GLfloat x, GLfloat y);
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
    void shot()
    {
        Gunshot *s = takeShoot();
        s->draw();
        gunshots.push_back(s);
    };
    void move()
    {
        takeMoviment();
    };
};

#endif /* OPPONENT_H */
