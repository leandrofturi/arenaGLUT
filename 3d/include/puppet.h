#ifndef PUPPET_H
#define PUPPET_H
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include "geometries.h"
#include <cstdio>

class Puppet
{
    GLfloat gX = 0.0;
    GLfloat gY = 0.0;
    GLfloat gZ = 0.0;
    GLfloat gSpeed = 50.0;

    OBJ *head;
    GLuint texturePuppet;

public:
    void init();
    void draw();
    void walk(double inc);
    void rotate(double inc);

    GLfloat getX()
    {
        return gX;
    }
    GLfloat getY()
    {
        return gY;
    }
    GLfloat getZ()
    {
        return gZ;
    }
};

#endif /* PUPPET_H */
