#ifndef GUNSHOT_H
#define GUNSHOT_H
#include <GL/gl.h>
#include <GL/glu.h>

class Gunshot
{
    GLfloat gXInit;
    GLfloat gYInit;
    GLfloat gX;
    GLfloat gY;
    GLfloat gDirectionAng;
    GLfloat gSpeed;

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
    };
    void draw()
    {
        drawGunshot(gX, gY);
    };
    void move();
    bool valid();
    void getPos(GLfloat &xOut, GLfloat &yOut)
    {
        xOut = gX;
        yOut = gY;
    };
};

#endif /* GUNSHOT_H */
