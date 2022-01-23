#ifndef BLOCK_H
#define BLOCK_H
#include <GL/gl.h>
#include <GL/glu.h>

class Block
{
    GLfloat gX;
    GLfloat gY;
    GLfloat gWidth;
    GLfloat gHeight;
    GLfloat gR;
    GLfloat gG;
    GLfloat gB;

private:
    void drawBlock(GLfloat x, GLfloat y);

public:
    Block(GLfloat x, GLfloat y, GLfloat width, GLfloat height, GLfloat R, GLfloat G, GLfloat B)
    {
        gX = x;
        gY = y;
        gWidth = width;
        gHeight = height;
        gR = R;
        gG = G;
        gB = B;
    };
    void draw()
    {
        drawBlock(gX, gY);
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
    GLfloat getWidth()
    {
        return gWidth;
    };
    GLfloat getHeight()
    {
        return gHeight;
    };
};

#endif /* BLOCK_H */
