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

    GLuint floorTexture;
    GLuint displayList;

public:
    Block(GLfloat x, GLfloat y, GLfloat z, GLfloat width, GLfloat height, GLfloat depth)
    {
        gX = x;
        gY = y;
        gZ = z;
        gWidth = width;
        gHeight = height;
        gDepth = depth;
        
        init();
    };

    void init();
    void draw();
    GLfloat getX()
    {
        return gX - gWidth / 2.0;
    };
    GLfloat getY()
    {
        return gY + gHeight / 2.0;
    };
    GLfloat getZ()
    {
        return gZ + gDepth / 2.0;
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
