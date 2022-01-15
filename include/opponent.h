#ifndef OPPONENT_H
#define OPPONENT_H
#include <GL/gl.h>
#include <GL/glu.h>

class Opponent
{
    GLfloat gX;
    GLfloat gY;
    GLfloat gRadius;
    GLfloat gR;
    GLfloat gG;
    GLfloat gB;

private:
    void drawOpponent(GLfloat x, GLfloat y);

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
};

#endif /* OPPONENT_H */
