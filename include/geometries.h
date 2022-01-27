#ifndef GEOMETRIES_H
#define GEOMETRIES_H
#include <GL/gl.h>
#include <GL/glu.h>

namespace Geometries
{
    float toRad(float theta);
    void drawRect(GLfloat height, GLfloat width, GLfloat R, GLfloat G, GLfloat B);
    void drawCircle(GLfloat radius, GLfloat R, GLfloat G, GLfloat B);
    void movePoint(GLfloat &x, GLfloat &y, GLfloat angle, GLfloat step);
    void rotatePoint(GLfloat cx, GLfloat cy, GLfloat angle, GLfloat &x, GLfloat &y);
    bool intersects(GLfloat R, GLfloat Xc, GLfloat Yc, GLfloat X1, GLfloat Y1, GLfloat X2, GLfloat Y2);
    bool intersects(GLfloat Aleft, GLfloat Aright, GLfloat Atop, GLfloat Abottom, GLfloat Bleft, GLfloat Bright, GLfloat Btop, GLfloat Bbottom);
}

#endif /* GEOMETRIES_H */
