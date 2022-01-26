#ifndef GUNSHOT_H
#define GUNSHOT_H
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>

class Gunshot
{
    GLfloat gXInit;
    GLfloat gYInit;
    GLfloat gX;
    GLfloat gY;
    GLfloat gDirectionAng;
    GLfloat gSpeed;
    GLfloat gR;
    GLfloat gG;
    GLfloat gB;

private:
    void drawGunshot(GLfloat x, GLfloat y);

public:
    Gunshot(GLfloat x, GLfloat y, GLfloat directionAng, GLfloat speed)
    {
        gXInit = x;
        gYInit = y;
        gX = x;
        gY = y;
        gDirectionAng = directionAng;
        gSpeed = speed;
        gR = ((double)rand() / (RAND_MAX));
        gG = ((double)rand() / (RAND_MAX));
        gB = ((double)rand() / (RAND_MAX));

        GLfloat ViewingWidth = 500.0;
        GLfloat ViewingHeight = 500.0;
    };
    void draw()
    {
        drawGunshot(gX, gY);
    };
    void move();
    bool valid();
    GLfloat getX()
    {
        return gX;
    };
    GLfloat getY()
    {
        return gY;
    };
    GLfloat getRadius();
};

#endif /* GUNSHOT_H */
