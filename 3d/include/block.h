#ifndef BLOCK_H
#define BLOCK_H
#include <GL/gl.h>
#include <GL/glu.h>

class Block
{
    GLfloat gX;
    GLfloat gY;
    GLfloat gZ;
    GLfloat gWidth;
    GLfloat gHeight;
    GLfloat gDepth;

public:
    Block(GLfloat x, GLfloat y, GLfloat z, GLfloat width, GLfloat height, GLfloat depth)
    {
        gX = x;
        gY = y;
        gZ = z;
        gWidth = width;
        gHeight = height;
        gDepth = depth;
    };

    void draw();
    GLfloat getX()
    {
        return gX;
    };
    GLfloat getY()
    {
        return gY;
    };
    GLfloat getZ()
    {
        return gZ;
    };
    GLfloat getWidth()
    {
        return gWidth;
    };
    GLfloat getHeight()
    {
        return gHeight;
    };
    GLfloat getDepth()
    {
        return gDepth;
    };
};

#endif /* BLOCK_H */
