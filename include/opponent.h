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
    void move(GLfloat dx, GLfloat dy)
    {
        gX += dx;
        gY += dy;
    };
    GLfloat getX()
    {
        return gX;
    };
    GLfloat getY()
    {
        return gY;
    };
    void setX(GLfloat x)
    {
        gX = x;
    };
    void setY(GLfloat x)
    {
        gY = x;
    };
};

#endif /* OPPONENT_H */
